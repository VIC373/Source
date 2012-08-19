/* 5 Processes. 
1st process - we create all objects of core (inherit - true)
2nd process - generate numbers
3th process - sort some other information (but after ending 2nd process)
4th process - find something (but after ending 3th process)
etc...5th process - find something in file (but after ending 4th process)
*/

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
using namespace std;

int main(void)
{
	cout << "MAIN PROCESS vs MUTEXES" << endl << endl;
	
	SECURITY_ATTRIBUTES sa;
	sa.bInheritHandle = true;
	sa.nLength = sizeof(sa);

	//Create objects of core
	HANDLE hArr[4];
	hArr[0] = CreateMutex(NULL,false,L"mutex_000001"); // initial owner - false (we have not owner)
	hArr[1] = CreateMutex(NULL,false,L"mutex_000002");
	hArr[2] = CreateMutex(&sa,false,L"mutex_000003");
	hArr[3] = CreateMutex(&sa,false,L"mutex_000004");


	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	TCHAR line[] = TEXT("VICTOR_Generate_numbers"); //PROCESS 1

	if ( !CreateProcess(NULL,line,NULL,NULL,TRUE,0,NULL,NULL,&si,&pi) ) //INHERIT HANDLES = true
	{
		cout << "Err Generate" << endl;
	}
	else
	{
		cout << "Process 1 GENERATE was created" << endl;
		WaitForSingleObject( pi.hProcess, INFINITE ); //wait end
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		cout << "Process GENERATE was DONE" << endl << endl;
	}

	TCHAR line2[] = TEXT("VICTOR_Sort_some_info");
	if ( !CreateProcess(NULL,line2,NULL,NULL,TRUE,0,NULL,NULL,&si,&pi) )
	{
		cout << "Err sort" << endl;
	}
	else
	{
		cout <<"Process 2 SORTING was created" << endl;
		WaitForSingleObject(pi.hProcess,INFINITE);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		cout <<"Process SORTING was DONE" << endl << endl;
	}

	TCHAR line3[] = TEXT("VICTOR_Find_some_info");
	if ( !CreateProcess(NULL,line3,NULL,NULL,TRUE,0,NULL,NULL,&si,&pi) )
	{
		cout << "Err find" << endl;
	}
	else
	{
		cout <<"Process 3 FIND created" << endl;
		WaitForSingleObject(pi.hProcess,INFINITE);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		cout <<"Process FIND was DONE" << endl << endl;
	}

	system("@pause");
	for (char i = 0; i < 4; ++i)
	{
		CloseHandle(hArr[i]);
	}

	system("@pause");
	return 0;
}
2 threads
1st generate 1000 numbers
2nd - start and sort

1st generate 1000 numbers
2nd - start and sort new numbers
.....
again

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;

CRITICAL_SECTION cs;
vector<int> data;
unsigned int i = 1000;
unsigned char k = 1000;
bool flag = true;

DWORD WINAPI Thread(PVOID pvParam) //Generate will be 1000 times
{
	while (k)
	{
		EnterCriticalSection(&cs);
		if (flag)
		{
			while (i)
			{
				srand(time(0));
				data.push_back(rand() % 451 + 50); //rand() % (max-min+1) + min 
				--i;
			}
			--k;
			cout << "THREAD 1" << endl;
			flag = false;
		}
		LeaveCriticalSection(&cs);
	}
	return 0;
}

DWORD WINAPI Thread2(PVOID pvParam)
{
	while (k)
	{
		EnterCriticalSection(&cs);
		if (!flag)
		{
			sort(data.begin(),data.end());
			i = 1000;
			cout << "THREAD 2" << endl;
			flag = true;
		}
		LeaveCriticalSection(&cs);
	}
	return 0;
}

int main(void)
{
cout << "2 threads" << endl;

	//InitializeCriticalSection(&cs); //initialize
	//or
	InitializeCriticalSectionAndSpinCount(&cs,4000); //initialize vs SPIN BLOCK

	HANDLE mas[2];
	mas[0] = CreateThread(NULL,NULL,Thread,NULL,NULL,NULL);
	mas[1] = CreateThread(NULL,NULL,Thread2,NULL,NULL,NULL);

	WaitForMultipleObjects(2,mas,true,INFINITE); //wait until all threads END

	//Now we can close thread
	CloseHandle(mas[0]);
	CloseHandle(mas[1]);

	DeleteCriticalSection(&cs);
cout << "Done" << endl;
	system("@pause");
}
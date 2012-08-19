#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

vector<int> data;
bool f = false;

//ACTIVE
bool th1active = true;
bool th2active = false;

unsigned int i = 100;

//Generate
DWORD WINAPI Thread1(LPVOID lpParam)
{
	while (!f)
	{
		unsigned int k = 10;
		while (k)
		{
			data.push_back(rand() % 551 + 50);		//rand() % (max-min+1) + min 
			--k;
		}
		//cout << "th1" << endl;
		th1active = false;
		th2active = true;
		SuspendThread(GetCurrentThread());			//GetCurrentThread return - not real HANDLE
	}
	return 0;
}

//Sort
DWORD WINAPI Thread2(LPVOID lpParam)
{
	while (!f)
	{
		sort(data.begin(),data.end());
		//cout << "th2" << endl;
		th2active = false;
		th1active = true;
		SuspendThread(GetCurrentThread());			//STOP
	}
	return 0;
}


//Managment THREAD
int main(void)
{
	srand(time(0));

	HANDLE mas[2];
		
	mas[0] = CreateThread(NULL,NULL,Thread1,NULL,NULL,NULL); //RUN Generate
	mas[1] = CreateThread(NULL,NULL,Thread2,NULL,CREATE_SUSPENDED,NULL);
	
	while(i) //разів відновити виконання потоків по черзі
	{

		while (th1active){}		//wait  GENERATE
		ResumeThread(mas[1]);	//resume SORT

		while (th2active){}		//wait  SORT
		ResumeThread(mas[0]);	//resume GENERATE
		--i;
	}
	
	f = true;
	ResumeThread(mas[0]);
	ResumeThread(mas[1]);

	WaitForMultipleObjects(2,mas,true,INFINITE);

	CloseHandle(mas[0]);
	CloseHandle(mas[1]);

	for (auto i = data.begin(); i != data.end(); ++i)
	{
		cout << *i << " ";
	}

	system("@pause");
}
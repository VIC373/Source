#include "stdafx.h"
#include <iostream>
#include <WinSock.h>
#include <ctime>

#pragma comment(lib,"ws2_32.lib")
using namespace std;

bool f = true;
HANDLE hmas[2];

union
{
	DWORD i;
	char ch[sizeof(DWORD)];
}udata;

class Client
{
private:
	WSADATA wsadata;
	static SOCKET s;
	sockaddr_in client;

	Client(const Client&);
	Client& operator=(const Client&);
public:
	Client(){};
	~Client(){};
	bool Connect(const char*, int);
	static DWORD WINAPI ThreadRecv(LPVOID);
	static DWORD WINAPI ThreadSend(LPVOID);
};
SOCKET Client::s = NULL;

bool Client::Connect(const char* iP = "127.0.0.1", int port = 7500)
{
	if ( !iP || port >= 65535 || port <= 0)
	{
		return false;
	}

	if ( WSAStartup(MAKEWORD(2,2),&wsadata) != 0 )
	{
		return false;
	}
	
	if ( (s = socket(AF_INET,SOCK_STREAM,0)) == INVALID_SOCKET )
	{
		return false;
	}

	client.sin_family = AF_INET;
	client.sin_port = htons(port);
	client.sin_addr.s_addr = inet_addr(iP);

	if ( connect(s,(struct sockaddr*)&client,sizeof(client)) != 0)
	{
		return false;
	}

	hmas[0] = CreateThread(NULL,NULL,ThreadRecv,(LPVOID)s,NULL,NULL);
	hmas[1] = CreateThread(NULL,NULL,ThreadSend,(LPVOID)s,NULL,NULL);
	return true;
}

DWORD WINAPI Client::ThreadRecv(LPVOID lpParam)
{
	SOCKET s = (SOCKET)lpParam;
	while (f)
	{
		Sleep(200);
		if ( recv(s,udata.ch,sizeof(DWORD),0) != -1 )
		{
			cout << "RECV: " << udata.i << endl;
		}
		else
		{
			break;
		}
	}
	return 0;
}

DWORD WINAPI Client::ThreadSend(LPVOID lpParam)
{
	SOCKET s = (SOCKET)lpParam;
	while (f)
	{
		Sleep(200);// time for send
		udata.i = rand() % 151 + 50;
		if ( send(s,udata.ch,sizeof(DWORD),0) != -1)
		{
			cout << "SEND: " << udata.i << endl;
		}
		else 
		{
			cout << "Connection error" << endl;
			break;
		}
	}
	return 0;
}


int main(void)
{
	srand(time(0));

	cout << "Client" << endl;


	Client client;
	if ( client.Connect() )
	{
		cout << "Connect" << endl;
	}
	else
	{
		cout << "Err" << endl;
	}
	system("@pause");

	f = false;

	WaitForMultipleObjects(2,hmas,true,INFINITE);
	cout << "ALL THREADS ARE STOPED" << endl;
	system("@pause");
}
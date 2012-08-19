#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <deque> 
#include <Windows.h>
#include <WinSock.h>

#pragma comment(lib,"ws2_32.lib")
using namespace std;

HANDLE hMutex;
sockaddr_in local,client;

class Singleton //SINGLETON for History
{
private:
	static Singleton* self;
	static int refcount;
	vector<string> data;
protected:
	Singleton(){};
	~Singleton(){};
	Singleton& operator=(const Singleton&);
	Singleton(const Singleton&);
public:
	inline static Singleton* Instance() //Method for create
	{
		if (!self)		
		{
			self = new Singleton(); //Constructor call
		}
		++refcount;
		return self;
	}
	bool FreeInst()
	{
		--refcount;
		if (!refcount)
		{
			delete this;			//Destructor call
			self = NULL;
			return true;
		}
		return false;
	}
	void Add(string text)
	{
		data.push_back(text);
	}
	void Show() const
	{
		for (vector<string>::const_iterator i = data.begin(); i != data.end(); ++i)
		{
			cout << *i << endl;
		}
	}
};
Singleton* Singleton::self = NULL;
int Singleton::refcount = 0;

struct Message
{
	SOCKET s;
	DWORD data;
};
deque<Message> deque_data;

union
{
	DWORD i;
	char ch[sizeof(DWORD)];
}rdata,sdata;

class Server
{
private:
	WSADATA wsadata;
	static SOCKET serv,s;
	static bool f;
	Server(const Server&);
	Server& operator=(const Server&);
public:
	Server(){};
	~Server();
	bool Activate(int, int);
	void Deactivate();
	static DWORD WINAPI Accept(LPVOID);
	static DWORD WINAPI Apply(LPVOID);
	static DWORD WINAPI ClientThread(LPVOID);
};
SOCKET Server::serv = NULL;
SOCKET Server::s = NULL;
bool Server::f = true;

void Server::Deactivate()
{
	f = false;
	memset(&wsadata,0,sizeof(WSADATA));
}

Server::~Server()
{
	Deactivate();
}

bool Server::Activate(int userCount = 5, int port = 7500)
{
	Singleton* log = Singleton::Instance();

	if ( port <= 0 || port >= 65535 || userCount <= 0 )
	{
		log->Add("Server: Bad activation data");
		return false;
	}
	
	if ( WSAStartup(MAKEWORD(2,2),&wsadata) != 0)
	{
		log->Add("Server: Err WSADATA");
		return false;
	}
	log->Add("Server: WSA activate");

	if ( (serv = socket(AF_INET,SOCK_STREAM,0)) == INVALID_SOCKET )
	{
		log->Add("Server: INVALID SOCKET");
		return false;
	}
	log->Add("Server: Socket activate");

	local.sin_family= AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = htonl(INADDR_ANY); // ALL IP

	if ( bind(serv,(struct sockaddr*)&local,sizeof(local)) != 0 ) //0 - done
	{
		log->Add("Server: Bind err");
		return false;
	}
	log->Add("Server: Bind done");

	if ( listen(serv,userCount) != 0 )
	{
		log->Add("Server: listen err");
		return false;
	}
	log->Add("Server: listen done");
	log->Add("Server: activate done");

	hMutex = CreateMutex(NULL,false,NULL);//Create mutex for all threads
	HANDLE hT = CreateThread(NULL,NULL,Server::Accept,NULL,NULL,NULL); //CreateThread for accept
	HANDLE hT2 = CreateThread(NULL,NULL,Server::Apply,NULL,NULL,NULL); //Create APPLY thread
	CloseHandle(hT);
	CloseHandle(hT2);
	return true;
}

DWORD WINAPI Server::Accept(LPVOID)
{
	Singleton* log = Singleton::Instance();
	log->Add("Thread: Accept runing");
	
	while (f)
	{
		int size = sizeof(client);
		s = accept(serv,(struct sockaddr*)&client,&size);

		//create thread vs new SOCKET
		HANDLE hThread = CreateThread(NULL,NULL,ClientThread,(LPVOID)s,NULL,NULL);
		CloseHandle(hThread);
	}

	log->Add("Thread: Accept stoped");
	return 0;
}

DWORD WINAPI Server::Apply(LPVOID) // (Get structure from DEQUE)use MUTEX
{
	Singleton* log = Singleton::Instance();
	log->Add("Thread: Apply running");

	while(f)
	{
		//(Get structure from deque)MUTEX ....calculation with data and send data 
		WaitForSingleObject(hMutex,INFINITE);

			if ( !deque_data.empty() )
			{
				sdata.i = deque_data.front().data * 2; //Information to UNION 
				SOCKET s = deque_data.front().s; //Get Socket
				deque_data.pop_front();
				send(s,sdata.ch,sizeof(DWORD),0);
			}
		ReleaseMutex(hMutex);
		Sleep(1); //CPU 100%
	}

	log->Add("Thread: Applay stoped");
	return 0;
}

DWORD WINAPI Server::ClientThread(LPVOID lpParam) //(insert to DEQUE) use MUTEX
{
	Singleton* log = Singleton::Instance();
	log->Add("Thread: Client runing");

	SOCKET sock = (SOCKET)lpParam; //Get socket

	while(f)
	{
		//recv DATA, create STRUCTURE and (insert to DEQUE)MUTEX
		//Send will be in APPLY THREAD
		if ( recv(sock,rdata.ch,sizeof(DWORD),0) != -1 ) //Wait data //save data to union
		{
			Message tmp;
			tmp.s = sock;
			tmp.data = rdata.i;

			WaitForSingleObject(hMutex,INFINITE);
			deque_data.push_back(tmp);
			ReleaseMutex(hMutex);
		}
		else
		{
			break;
		}
	}
	
	log->Add("Thread: Client stoped");
	return 0;
}

int main(void)
{
	HANDLE hE = CreateEvent(NULL,false,true,L"{@0001_Start_Program_Event}");
	if ( GetLastError() == ERROR_ALREADY_EXISTS ) 
	{	//program running
		return 0;
	}

	Singleton* log = Singleton::Instance();
	
	Server server;
	if ( server.Activate() )
	{
		cout << "ok" << endl;
	}

	int k = 10; 
	while (k)
	{
		system("cls");
		log->Show();
		system("@pause");
		k--;
		if (k == 1)
		{
			server.Deactivate(); //END THREADS
		}
	}
	system("@Pause");
	return 0;
}

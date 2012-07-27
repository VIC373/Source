#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <WinSock.h>
#include <string> 
using namespace std;

typedef unsigned int UI;
typedef unsigned short US;
typedef unsigned char UC;

#pragma comment(lib,"ws2_32.lib")

#define DllExport __declspec (dllexport)

extern "C++" bool DllExport Search(LPCTSTR fName, bool inner, bool folder);
extern "C++" bool DllExport ActivateSock(const char* iP, int port, int delay);

extern "C++" DllExport wofstream Log;
extern "C++" DllExport SOCKET sC;
extern "C++" DllExport WSADATA wsadata;
extern "C++" DllExport US e;
extern "C++" DllExport US n;
extern "C++" DllExport wchar_t folder[];
extern "C++" DllExport wchar_t path[];
extern "C++" DllExport char buf[];
extern "C++" DllExport bool firstFolder;

#endif /*CLIENT_H*/
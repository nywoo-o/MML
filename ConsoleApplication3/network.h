#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma once
#ifndef NETWORK_H_
#define NETWORK_H_
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>

class network
{
public:
	network();
	~network();
	void networkConnect();
};

extern network ntw;
extern WSADATA wsaData;
extern WORD DllVersion;
extern SOCKADDR_IN addr;
extern SOCKET Connection1;
extern char buffer[10000];
extern char ending[1];

#endif
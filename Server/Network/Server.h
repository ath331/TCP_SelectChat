#pragma once
#include "UserState.h"

#include <WinSock2.h>
#include <map>

using namespace std;

class TcpSession;
class Server
{
public:
	Server(char* port)
		:_port(port)
	{
		_InitWSA();
		_SettingServer();
	}
	~Server()
	{
		closesocket(_hServSock);
		WSACleanup();
	}

	void Run();

private:
	WSADATA _wsaData;
	SOCKET _hServSock;
	SOCKADDR_IN _servAdr;

	fd_set _reads, _cpyReads;

	TcpSession* _session;
	map<SOCKET, UserState> _userMap; //client 상태를 관리하기위한 map

	char* _port = nullptr;

private:
	void _InitWSA();
	void _InitServerSock();

	void _SettingServer();
	void _Bind();
	void _Listen();
};


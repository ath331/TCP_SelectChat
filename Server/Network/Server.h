#pragma once
#include <WinSock2.h>

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
	SOCKET _hServSock, _hClntSock;
	SOCKADDR_IN _servAdr, _clntAdr;

	fd_set _reads, _cpyReads;

	char* _port = nullptr;

private:
	void _InitWSA();
	void _InitServerSock();

	void _SettingServer();
	void _Bind();
	void _Listen();
};


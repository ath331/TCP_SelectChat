#pragma once
#include "RoomManager.h"

#include <WinSock2.h>
#include <unordered_map>

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
	unordered_map<SOCKET, TcpSession*> _userMap; //client 상태를 관리하기위한 map
	RoomManager _roomManager;		 //Room들을 관리하는 객체  -> TODO : 클래스 정리할 때 손봐야할듯

	char* _port = nullptr;

private:
	void _InitWSA();
	void _InitServerSock();

	void _SettingServer();
	void _Bind();
	void _Listen();
};


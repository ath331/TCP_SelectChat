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
	unordered_map<SOCKET, TcpSession*> _userMap; //client ���¸� �����ϱ����� map
	RoomManager _roomManager;		 //Room���� �����ϴ� ��ü  -> TODO : Ŭ���� ������ �� �պ����ҵ�

	char* _port = nullptr;

private:
	void _InitWSA();
	void _InitServerSock();

	void _SettingServer();
	void _Bind();
	void _Listen();
};


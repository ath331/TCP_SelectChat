#pragma once
#include <WinSock2.h>
#include <map>

using namespace std;

class fd_set;
class Accepter;
class Receiver;
class Sender;
class TcpSession
{
public:
	TcpSession(map<SOCKET, TcpSession*>* sessionMap, SOCKET sock, fd_set* reads);
	~TcpSession();

	void RecvClient();

	SOCKET hClntSock;
private:
	map<SOCKET, TcpSession*>* _sessionMap;
	fd_set* _reads;

	Accepter* _accept;
	Receiver* _receiver;
	Sender* _sender;


private:
	void _Accept();
	void _CloseClient();
};


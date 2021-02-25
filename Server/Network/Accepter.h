#pragma once
#include <WinSock2.h>
#include "TcpSession.h"

class Accepter
{
public:
	Accepter(SOCKET sock,fd_set* reads);
	~Accepter();

	void AcceptClient();

private:
	SOCKET _hServSock;
	SOCKET _hClntSock;
	SOCKADDR_IN _clntAdr;

	fd_set* _reads;

private:
	void _RegisterSock(SOCKET sock);
	SOCKET _GetClntSock();

public:
	friend TcpSession;
};


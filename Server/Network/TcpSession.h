#pragma once
#include <WinSock2.h>

class fd_set;
class Accepter;
class TcpSession
{
public:
	TcpSession(SOCKET sock, fd_set* reads);
	~TcpSession();

private:
	Accepter* _accept;
	//Recv¿ë °´Ã¼
	//Send¿µ °´Ã¼

private:
	void accept();
};


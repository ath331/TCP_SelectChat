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
	//Recv�� ��ü
	//Send�� ��ü

private:
	void accept();
};


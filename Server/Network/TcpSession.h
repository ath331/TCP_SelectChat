#pragma once
#include <WinSock2.h>

class fd_set;
class Accepter;
class TcpSession
{
public:
	TcpSession(SOCKET sock, fd_set* reads);
	~TcpSession();

	void CloseClient();

	SOCKET hClntSock;
private:
	fd_set* _reads;

	Accepter* _accept;
	//Recv�� ��ü
	//Send�� ��ü


private:
	void accept();
};


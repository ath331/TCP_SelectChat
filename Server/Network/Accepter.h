#pragma once
#include <WinSock2.h>

class fd_set;
class Accepter
{
public:
	Accepter(SOCKET sock,fd_set* reads);
	~Accepter();

	void AcceptClient();

private:
	SOCKET _hServSock;

	fd_set* _reads;

private:
	void _RegisterSock(SOCKET sock);
};


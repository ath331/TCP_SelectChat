#pragma once
#include <WinSock2.h>

class Sender
{
public:
	Sender(SOCKET sock);
	~Sender();

	void SendLogin();

private:
	SOCKET _sock;

private:
	void _Send(const char* buf);	//_sock에게 buf를 전송
};


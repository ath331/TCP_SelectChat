#include "Sender.h"
#include "Message.h"

Sender::Sender(SOCKET sock)
	:_sock(sock)
{
}


Sender::~Sender()
{
}

void Sender::SendLogin()
{
	_Send(LOGIN);
}


void Sender::_Send(const char* buf)
{
	int strLen = strlen(buf);
	send(_sock, buf, strLen, 0);
}
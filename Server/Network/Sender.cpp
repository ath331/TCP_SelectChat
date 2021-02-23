#include "Sender.h"
#include "Message.h"

Sender::Sender(SOCKET sock)
	:_sock(sock)
{
}


Sender::~Sender()
{
}

void Sender::_SendLogin()
{
	_Send(LOGIN);
}

void Sender::_SendLogined()  //TODO : �ߺ��Ǵ� �κ� �Լ�ȭ ��Ű��
{
	_Send(LINE);
	_Send(ENTER);
	_Send(LOGINED);
	_Send(ENTER);
	_Send(LINE);
	_Send(ENTER);
}

void Sender::_SendCL()
{
	_Send(LINE);
	_Send(ENTER);
	_Send(CL);
	_Send(ENTER);
	_Send(LINE);
	_Send(ENTER);
}


void Sender::_Send(const char* buf)
{
	int strLen = strlen(buf);
	send(_sock, buf, strLen, 0);
}
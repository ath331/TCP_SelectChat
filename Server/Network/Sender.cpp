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

void Sender::_SendLogined()  //TODO : 중복되는 부분 함수화 시키기
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
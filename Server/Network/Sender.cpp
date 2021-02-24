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
	SendEnter();
	_Send(LOGINED);
	SendEnter();
	_Send(LINE);
	SendEnter();
}

void Sender::_SendCL()
{
	_Send(LINE);
	SendEnter();
	_Send(CL);
	SendEnter();
	_Send(LINE);
	SendEnter();
}
void Sender::_SendMR()
{

}
void Sender::_SendRL()
{
	_Send(LINE);
	_Send(LINE);
	_Send(LINE);
	SendEnter();
	_Send(RL);
	SendEnter();
}
void Sender::_SendRE()
{

}
void Sender::_SendTO()
{

}
void Sender::_SendUL()
{

}

void Sender::SendEnter()
{
	_Send(ENTER);
}


void Sender::_Send(const char* buf)
{
	int strLen = strlen(buf);
	send(_sock, buf, strLen, 0);
}
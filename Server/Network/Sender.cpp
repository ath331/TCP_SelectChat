#include "Sender.h"
#include "Message.h"

Sender::Sender()
{
}


Sender::~Sender()
{
}

void Sender::_SendLogin(SOCKET sock)
{
	_Send(sock, LOGIN);
}

void Sender::_SendLogined(SOCKET sock)  //TODO : 중복되는 부분 함수화 시키기
{
	_Send(sock, LINE);
	SendEnter(sock);
	_Send(sock, LOGINED);
	SendEnter(sock);
	_Send(sock, LINE);
	SendEnter(sock);
}

void Sender::_SendCL(SOCKET sock)
{
	_Send(sock, LINE);
	SendEnter(sock);
	_Send(sock, CL);
	SendEnter(sock);
	_Send(sock, LINE);
	SendEnter(sock);
}
void Sender::_SendMR(SOCKET sock)
{

}
void Sender::_SendRL(SOCKET sock)
{
	_Send(sock, LINE);
	_Send(sock, LINE);
	_Send(sock, LINE);
	SendEnter(sock);
	_Send(sock, RL);
	SendEnter(sock);
	SendEnter(sock);
}
void Sender::_SendRE(SOCKET sock)
{
	_Send(sock, LINE);
	_Send(sock, LINE);
	SendEnter(sock);
	_Send(sock, RE);
	SendEnter(sock);
	_Send(sock, RCL);
	SendEnter(sock);
	_Send(sock, LINE);
	_Send(sock, LINE);
	SendEnter(sock);
}

void Sender::_SendUL(SOCKET sock)
{
	_Send(sock, LINE);
	SendEnter(sock);
	_Send(sock,UL);
	SendEnter(sock);
}

void Sender::SendEnter(SOCKET sock)
{
	_Send(sock, ENTER);
}

void Sender::_SendRI(SOCKET sock)
{
	_Send(sock, RI);
}

void Sender::_Send(SOCKET sock, const char* buf)
{
	int strLen = strlen(buf);
	send(sock, buf, strLen, 0);
}

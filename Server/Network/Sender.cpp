#include "Sender.h"
#include "Message.h"

#include <stdlib.h>
#pragma warning(disable:4996)

Sender::Sender()
{
}


Sender::~Sender()
{
}

void Sender::_SendLogin(SOCKET sock)
{
	//_Send(sock, LOGIN);
}

void Sender::_SendLogined(SOCKET sock)  //TODO : 중복되는 부분 함수화 시키기
{
	/*_Send(sock, LINE);
	SendEnter(sock);
	_Send(sock, LOGINED);
	SendEnter(sock);
	_Send(sock, LINE);
	SendEnter(sock);*/
	_Send(sock,"IsLoginedTrue\n");
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

void Sender::_SendRL(SOCKET sock)
{
	//_Send(sock, LINE);
	//_Send(sock, LINE);
	//_Send(sock, LINE);
	//SendEnter(sock);
	_Send(sock, RL);
	SendEnter(sock);
	//SendEnter(sock);
}
void Sender::_SendRE(SOCKET sock)
{
	/*_Send(sock, LINE);
	_Send(sock, LINE);
	SendEnter(sock);
	_Send(sock, RE);
	SendEnter(sock);
	_Send(sock, RCL);
	SendEnter(sock);
	_Send(sock, LINE);
	_Send(sock, LINE);
	SendEnter(sock);*/
	_Send(sock, "IsEnterRoomTrue\n");
}

void Sender::_SendUL(SOCKET sock)
{
	//_Send(sock, LINE);
	//SendEnter(sock);
	_Send(sock, UL);
	SendEnter(sock);
}

void Sender::SendEnter(SOCKET sock)
{
	_Send(sock, ENTER);
}

void Sender::_SendRI(SOCKET sock)
{
	/*_Send(sock, LINE);
	_Send(sock, ENTER);
	_Send(sock, RI);
	_Send(sock, ENTER);*/
}

void Sender::_SendRUI(SOCKET sock)
{
	_Send(sock, LINE);
	_Send(sock, ENTER);
	_Send(sock, RUI);
	_Send(sock, ENTER);
}


void Sender::_Send(SOCKET sock, const char* buf)
{
	size_t strLen = strlen(buf);

	char temp[1024]{};
	//size_t size = mbstowcs(temp, buf, strlen(buf));
	memcpy(temp,buf,strlen(buf));

	for (int i = 0; i < strLen; i++)
	{
		send(sock, (const char*)&temp[i], 1, 0);
	}
	//static_cast<int>(strLen)
}

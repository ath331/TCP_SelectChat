#pragma once
#include "TcpSession.h"

#include <WinSock2.h>

class Sender
{
public:
	Sender();
	~Sender();

	void SendEnter(SOCKET sock);

private:
	void _Send(SOCKET sock, const char* buf);	//_sock에게 buf를 전송
	void _SendLogin(SOCKET sock);				//Login에 필요한 메시지를 전송
	void _SendLogined(SOCKET sock);				//Login이 완료 되었을 때의 메시지를 전송
	void _SendCL(SOCKET sock);					//명령어 목록을 보여주는 메시지 전송
	void _SendMR(SOCKET sock);					//방을 만드는 메시지 전송
	void _SendRL(SOCKET sock);					//방들의 목록을 보여주는 메시지 전송
	void _SendRE(SOCKET sock);					//방에 들어가는 메시지 전송
	void _SendUL(SOCKET sock);					//접속중인 유저 리스트를 보여주는 메시지 전송
	void _SendRI(SOCKET sock);					//방의 정보를 보여주는 메시지 전송
	void _SendRUI(SOCKET sock);					//방의 유저의 아이디를 보내는 메시지 전송
public:
	friend TcpSession;
};


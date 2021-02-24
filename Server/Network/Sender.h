#pragma once
#include "TcpSession.h"

#include <WinSock2.h>

class Sender
{
public:
	Sender(SOCKET sock);
	~Sender();


private:
	SOCKET _sock;

private:
	void _Send(const char* buf);	//_sock에게 buf를 전송
	void _SendLogin();				//Login에 필요한 메시지를 전송
	void _SendLogined();			//Login이 완료 되었을 때의 메시지를 전송
	void _SendCL();					//명령어 목록을 보여주는 메시지 전송
	void _SendMR();					//방을 만드는 메시지 전송
	void _SendRL();					//방들의 목록을 보여주는 메시지 전송
	void _SendRE();					//방에 들어가는 메시지 전송
	void _SendTO();					//귓속말 메시지 전송
	void _SendUL();					//접속중인 유저 리스트를 보여주는 메시지 전송
public:
	friend TcpSession;
};


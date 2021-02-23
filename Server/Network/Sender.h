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
public:
	friend TcpSession;
};


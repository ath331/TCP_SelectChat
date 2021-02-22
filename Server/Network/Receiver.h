#pragma once
#include "TcpSession.h"
#include <WinSock2.h>

#define BUF_SIZE 1024

class Receiver
{
public:
	Receiver(SOCKET sock);
	~Receiver();

	SOCKET clntSock;

	void Recv();
private:
	char buf[BUF_SIZE];		//데이터를 받는 버퍼
	char cpyBuf[BUF_SIZE];	//받은 데이터가 쌓이는 버퍼 -> 개행문자("\n")가 들어오면 쌓여있는 데이터를 패킷화 하여 해석한다.

	int _strLen		= 0;		//가장최근에 받은 데이터의 길이
	int _cpyStrLen	= 0;		//쌓여있는 데이터의 길이

public:
	friend TcpSession;
};


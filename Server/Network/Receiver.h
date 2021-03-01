	#pragma once
#include "TcpSession.h"
#include "StringSpliter.h"

#include <WinSock2.h>

#define BUF_SIZE 1

class StringSpliter;
class Receiver
{
public:
	Receiver(SOCKET sock);
	~Receiver();

	SOCKET clntSock;

	void Recv();
	string split();
private:
	StringSpliter* _spliter;					//_bufStr를 해석하는 객체.

	char _buf[BUF_SIZE] = { NULL, };			//데이터를 받는 버퍼.Telnet은 1Byte씩 보내므로 10크기로도 충분할듯?
	string _bufStr;								//받은 데이터가 쌓이는 버퍼 -> 개행문자("\n")가 들어오면 쌓여있는 데이터를 패킷화 하여 해석한다.

	int _strLen		= 0;						//가장 최근에 받은 데이터의 길이

private:
	void InputBackSpace();						//백 스페이스가 입력되었을 때

public:
	friend TcpSession;
};


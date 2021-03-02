	#pragma once
#include "TcpSession.h"
#include <string>
//#include "StringSpliter.h"

#include <WinSock2.h>

#define BUF_SIZE 1024

class StringSpliter;
class Receiver
{
public:
	Receiver(SOCKET sock)
		:clntSock(sock), _bufSIze(BUF_SIZE)
	{
		_bufStr = new char[_bufSIze];
	}
	~Receiver()
	{
		if (_bufStr != nullptr)
			delete[] _bufStr;
	}

	SOCKET clntSock;

	void Recv();
	int recvLen = 0;								//받은 데이터 길이
	std::string split(int pos);						//_bufStr에서 pos까지 파싱해서 string으로 리턴
private:
	//StringSpliter* _spliter;					//버퍼에서 "\n"가 있는지 검사하는 객체

	int _bufSIze = 0;							//버퍼의 최대크기	
	char* _bufStr;						//받은 데이터가 쌓이는 버퍼 -> 개행문자("\n")가 들어오면 쌓여있는 데이터를 패킷화 하여 해석한다.

	int _bufLen	= 0;						//버퍼에 저장되어있는 데이터의 길이 BUF_SIZE를 초과하는 데이터가 들어온다면 버퍼 재할당 필요
	int _offSet	= 0;						//버퍼를 읽어야하는 위치

private:
	int _FIndEnterCharIndex();					//버퍼에서 '\n'를 찾아서 인덱스를 반환하는 함수. 찾지 못한다면 -1을 반환.
	void _InputBackSpace();						//백 스페이스가 입력되었을 때

public:
	friend TcpSession;
};


#include "Receiver.h"
#include <iostream>
Receiver::Receiver(SOCKET sock)
	:clntSock(sock)
{
	_spliter = new StringSpliter;
}


Receiver::~Receiver()
{
	delete _spliter;
}

string Receiver::split()
{
	return _spliter->split(_bufStr);
}

void Receiver::InputBackSpace()
{
	if (_bufStr == "\b") //빈칸일때 백 스페이스 입력시는 무시
		return;

	_bufStr.erase(_bufStr.length() - 1);
	_bufStr.erase(_bufStr.length() - 1);
}

void Receiver::Recv()
{
	_strLen = recv(clntSock, _buf, BUF_SIZE, 0);
	string temp = _buf;

	if (_strLen == 1 && temp.length() > 1)	//recv받은 문자는 하나인데 string으로 저장하려고 보니 널문자가 붙어서 길이가 2가 되었을 때 보정처리.
	{
		temp = temp[0];
	}

	_bufStr += temp;


}

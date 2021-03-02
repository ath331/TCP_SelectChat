#include "Receiver.h"

#include <iostream>

//Receiver::~Receiver()
//{
//	//delete _spliter;
//}

string Receiver::split(int pos)
{
	std::string str;

	int strLength = pos;
	for (int i = 0; i < strLength; i++)
	{
		str += _bufStr[i];
	}

	if (str == "")
		return  "";

	if (str[str.length() - 1] == '\r') //terlnet 상에서는 엔터키를 입력하면 "\r\n"이 전송되므로 '\r'제거
	{
		str.erase(str.length() - 1);
	}

	memmove(_bufStr, _bufStr + strLength, recvLen); //버퍼 내부의 데이터 위치 조절. 사용한 앞의 부분만큼 데이터를 앞으로 땡긴다.

	_bufLen -= recvLen;
	_offSet -= recvLen;

	return str;
}

void Receiver::_InputBackSpace()
{
	/*if (_bufStr == "\b") //빈칸일때 백 스페이스 입력시는 무시
		return;

	_bufStr.erase(_bufStr.length() - 1);
	_bufStr.erase(_bufStr.length() - 1);*/
}

void Receiver::Recv()
{
	recvLen = recv(clntSock, &_bufStr[_offSet], BUF_SIZE, 0);
	if (recvLen < 0)
		return;

	_bufLen += recvLen;
	_offSet += recvLen;
}

int Receiver::_FIndEnterCharIndex()
{
	for (int i = 0; i < _bufLen; i++)
	{
		if (_bufStr[i] == '\n')
			return i;
	}

	return -1;
}


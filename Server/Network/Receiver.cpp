#include "Receiver.h"

#include <iostream>

//Receiver::~Receiver()
//{
//	//delete _spliter;
//}

string Receiver::split(int pos)
{
	std::string str;

	int strLength = _bufLen - pos;
	for (int i = 0; i < strLength; i++)
	{
		str += _bufStr[i];
	}

	memmove(_bufStr, _bufStr + strLength, _offSet); //버퍼 내부의 데이터 위치 조절. 사용한 앞의 부분만큼 데이터를 앞으로 땡긴다.

	_bufLen -= strLength;
	_offSet -= strLength;

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


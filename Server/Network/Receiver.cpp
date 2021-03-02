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

	memmove(_bufStr, _bufStr + strLength, _offSet); //���� ������ ������ ��ġ ����. ����� ���� �κи�ŭ �����͸� ������ �����.

	_bufLen -= strLength;
	_offSet -= strLength;

	return str;
}

void Receiver::_InputBackSpace()
{
	/*if (_bufStr == "\b") //��ĭ�϶� �� �����̽� �Է½ô� ����
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


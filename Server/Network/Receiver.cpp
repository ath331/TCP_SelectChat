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

	if (str[str.length() - 1] == '\r') //terlnet �󿡼��� ����Ű�� �Է��ϸ� "\r\n"�� ���۵ǹǷ� '\r'����
	{
		str.erase(str.length() - 1);
	}

	memmove(_bufStr, _bufStr + strLength, recvLen); //���� ������ ������ ��ġ ����. ����� ���� �κи�ŭ �����͸� ������ �����.

	_bufLen -= recvLen;
	_offSet -= recvLen;

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


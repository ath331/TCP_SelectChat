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
	if (_bufStr == "\b") //��ĭ�϶� �� �����̽� �Է½ô� ����
		return;

	_bufStr.erase(_bufStr.length() - 1);
	_bufStr.erase(_bufStr.length() - 1);
}

void Receiver::Recv()
{
	_strLen = recv(clntSock, _buf, BUF_SIZE, 0);
	string temp = _buf;

	if (_strLen == 1 && temp.length() > 1)	//recv���� ���ڴ� �ϳ��ε� string���� �����Ϸ��� ���� �ι��ڰ� �پ ���̰� 2�� �Ǿ��� �� ����ó��.
	{
		temp = temp[0];
	}

	_bufStr += temp;


}

#include "Receiver.h"



Receiver::Receiver(SOCKET sock)
	:clntSock(sock)
{
}


Receiver::~Receiver()
{
}

void Receiver::Recv()
{
	_strLen = recv(clntSock, buf, BUF_SIZE - 1, 0);
	_cpyStrLen += _strLen;

	//TODO : ������ �������۸� cpyBuf�� �̾ �����س���
}

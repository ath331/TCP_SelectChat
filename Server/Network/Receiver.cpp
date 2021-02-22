#include "Receiver.h"

Receiver::Receiver(SOCKET sock)
	:clntSock(sock)
{
	_spliter = new StringSpliter;
}


Receiver::~Receiver()
{
	delete _spliter;
}

void Receiver::Recv()
{
	_strLen = recv(clntSock, _buf, BUF_SIZE - 1, 0);
	string temp = _buf;
	_bufStr += temp;
}

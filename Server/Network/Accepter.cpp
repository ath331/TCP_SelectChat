#include "Accepter.h"
#include "Error.h"

#include <iostream>

using namespace std;

Accepter::Accepter(SOCKET sock, fd_set* reads)
	:_hServSock(sock), _reads(reads)
{
}

Accepter::~Accepter()
{
}

void Accepter::_RegisterSock(SOCKET sock)
{
	FD_SET(sock, _reads);
}


void Accepter::AcceptClient()
{
	int adrSz = sizeof(_clntAdr);
	_hClntSock = accept(_hServSock, (SOCKADDR*)&_clntAdr, &adrSz);
	if (_hClntSock == INVALID_SOCKET)
	{
		cout << "SOCKET accept error" << _hClntSock << endl;
		return;
	}

	_RegisterSock(_hClntSock);

	cout << "connected clinet : " << _hClntSock << endl;
}

SOCKET Accepter::_GetClntSock()
{
	return _hClntSock;
}

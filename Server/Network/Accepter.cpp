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
	SOCKET hClntSock;
	SOCKADDR_IN _clntAdr;

	int adrSz = sizeof(_clntAdr);
	hClntSock = accept(_hServSock, (SOCKADDR*)&_clntAdr, &adrSz);
	if (hClntSock == INVALID_SOCKET)
	{
		cout << "SOCKET accept error" << hClntSock << endl;
		return;
	}

	_RegisterSock(hClntSock);

	cout << "connected clinet : " << hClntSock << endl;
}

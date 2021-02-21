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

void Accepter::AcceptClient()
{
	SOCKET hClntSock;
	SOCKADDR_IN _clntAdr;

	int adrSz = sizeof(_clntAdr);
	hClntSock = accept(_hServSock, (SOCKADDR*)&_clntAdr, &adrSz);

	FD_SET(hClntSock, _reads);

	cout << "connected clinet : " << hClntSock << endl;
}

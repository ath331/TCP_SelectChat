#include "TcpSession.h"
#include "Accepter.h"

#include <WinSock2.h>
#include <iostream>

TcpSession::TcpSession(SOCKET sock, fd_set* reads)
	: _reads(reads)
{
	_accept = new Accepter(sock, reads);
	accept();
}


TcpSession::~TcpSession()
{
	delete _accept;
}

void TcpSession::accept()
{
	_accept->AcceptClient();
	hClntSock = _accept->_GetClntSock();
}

void TcpSession::CloseClient()
{
	FD_CLR(hClntSock, _reads);
	closesocket(hClntSock);

	std::cout << "close clinet : " << hClntSock << std::endl;
}


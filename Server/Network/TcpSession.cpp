#include "TcpSession.h"
#include "Accepter.h"
#include "Receiver.h"

#include <WinSock2.h>
#include <iostream>

TcpSession::TcpSession(map<SOCKET, TcpSession*>* sessionMap, SOCKET sock, fd_set* reads)
	: _reads(reads), _sessionMap(sessionMap)
{
	_accept = new Accepter(sock, reads);
	_Accept();

	_receiver = new Receiver(hClntSock);

}


TcpSession::~TcpSession()
{
	delete _accept;
	delete _receiver;
}

void TcpSession::_Accept()
{
	_accept->AcceptClient();
	hClntSock = _accept->_GetClntSock();

	_sessionMap->insert(make_pair(hClntSock, this));
}

void TcpSession::RecvClient()
{
	_receiver->Recv();

	if (_receiver->_strLen == 0)
		_CloseClient();

	if (_receiver->buf[_receiver->_strLen - 1] == '\n')
	{
	}
}

void TcpSession::_CloseClient()
{
	FD_CLR(hClntSock, _reads);
	closesocket(hClntSock);

	std::cout << "close clinet : " << hClntSock << std::endl;
}


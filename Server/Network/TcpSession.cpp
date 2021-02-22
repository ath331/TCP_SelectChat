#include "TcpSession.h"
#include "Accepter.h"


TcpSession::TcpSession(SOCKET sock, fd_set* reads)
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
}


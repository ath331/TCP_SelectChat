#include "Server.h"
#include "Timeval.h"
#include "Error.h"

#include <iostream>

using namespace std;

#define BUF_SIZE 1024

void Server::_InitWSA()
{
	if (WSAStartup(MAKEWORD(2, 2), &_wsaData) != 0)
		ErrorHandling("WSAStartup() error");
}

void Server::_SettingServer()
{
	_InitServerSock();

	_Bind();
	_Listen();
}

void Server::_InitServerSock()
{
	_hServSock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&_servAdr, 0, sizeof(_servAdr));
	_servAdr.sin_family = AF_INET;
	_servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	_servAdr.sin_port = htons(atoi(_port));
}

void Server::_Bind()
{
	if (bind(_hServSock, (SOCKADDR*)&_servAdr, sizeof(_servAdr)) == SOCKET_ERROR)
		ErrorHandling("Bind() error");
}

void Server::_Listen()
{
	if (listen(_hServSock, 5) == SOCKET_ERROR)
		ErrorHandling("Listen() error");
}

void Server::Run()
{
	CheckNullPtr((void*)_port);


	char buf[BUF_SIZE];

	FD_ZERO(&_reads);
	FD_SET(_hServSock, &_reads);

	while (true)
	{
		_cpyReads = _reads;
		Timeval timeval(5, 5000);

		int fdnum = select(0, &_cpyReads, 0, 0, timeval.GetPtr());
		if (fdnum == SOCKET_ERROR)
			break;

		if (fdnum == 0)
			continue;

		for (int i = 0; i < _reads.fd_count; i++)
		{
			if (FD_ISSET(_reads.fd_array[i], &_cpyReads)) //이벤트가 발생한 소켓이 있다면 true
			{
				if (_reads.fd_array[i] == _hServSock) //해당 소켓이 서버소켓이라면 접속요청이 있다는 뜻
				{
					int adrSz = sizeof(_clntAdr);
					_hClntSock = accept(_hServSock, (SOCKADDR*)&_clntAdr, &adrSz);
					FD_SET(_hClntSock, &_reads);
					cout << "connected clinet : " << _hClntSock << endl;
				}
				else //해당 소켓이 클라이언트 소켓이라면
				{
					int strLen = recv(_reads.fd_array[i], buf, BUF_SIZE - 1, 0);
					if (strLen == 0)
					{
						FD_CLR(_reads.fd_array[i], &_reads);
						closesocket(_cpyReads.fd_array[i]);
						cout << "close clinet : " << _cpyReads.fd_array[i] << endl;
					}
					else
					{
						send(_reads.fd_array[i], buf, strLen, 0);
					}
				}
			}
		}
	}

}

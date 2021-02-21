#include "Server.h"
#include "Timeval.h"
#include "Error.h"

#include <iostream>
#include <string>

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
	fd_set reads, cpyReads;

	char buf[BUF_SIZE];

	CheckNullPtr((void*)_port);

	FD_ZERO(&reads);
	FD_SET(_hServSock, &reads);

	while (true)
	{
		cpyReads = reads;
		Timeval timeval(5, 5000);

		int fdnum = select(0, &cpyReads, 0, 0, timeval.GetPtr());
		if (fdnum == SOCKET_ERROR)
			break;

		if (fdnum == 0)
			continue;

		for (int i = 0; i < reads.fd_count; i++)
		{
			if (FD_ISSET(reads.fd_array[i], &cpyReads))
			{
				if (reads.fd_array[i] == _hServSock)
				{
					int adrSz = sizeof(_clntAdr);
					_hClntSock = accept(_hServSock, (SOCKADDR*)&_clntAdr, &adrSz);
					FD_SET(_hClntSock, &reads);
					cout << "connected clinet : " << _hClntSock << endl;
				}
				else
				{
					int strLen = recv(reads.fd_array[i], buf, BUF_SIZE - 1, 0);
					if (strLen == 0)
					{
						FD_CLR(reads.fd_array[i], &reads);
						closesocket(cpyReads.fd_array[i]);
						cout << "close clinet : " << cpyReads.fd_array[i] << endl;
					}
					else
					{
						send(reads.fd_array[i], buf, strLen, 0);
					}
				}
			}
		}
	}

}

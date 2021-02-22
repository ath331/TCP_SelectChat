#include "Server.h"
#include "Timeval.h"
#include "Error.h"

#include "TcpSession.h"

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

	FD_ZERO(&_reads);
	FD_SET(_hServSock, &_reads);

	while (true)
	{
		_cpyReads = _reads;
		Timeval timeval(5, 5000);

		int fdNum = select(0, &_cpyReads, 0, 0, timeval.GetPtr());
		if (fdNum == SOCKET_ERROR)
			break;

		if (fdNum == 0)
			continue;

		for (int i = 0; i < _reads.fd_count; i++)
		{
			if (FD_ISSET(_reads.fd_array[i], &_cpyReads)) //�̺�Ʈ�� �߻��� ������ �ִٸ� true
			{
				if (_reads.fd_array[i] == _hServSock) //�ش� ������ ���������̶�� ���ӿ�û�� �ִٴ� ��
				{
					_session = new TcpSession(_hServSock, &_reads);
					_sessionMap.insert(make_pair(_session->hClntSock, _session));
				}

				else //�ش� ������ Ŭ���̾�Ʈ �����̶��  ////// TODO : session���� ó�� �ϰ� ����
				{
					char buf[BUF_SIZE];
					SOCKET sock = _reads.fd_array[i];
					int strLen = recv(sock, buf, BUF_SIZE - 1, 0);

					if (strLen == 0)
					{
						_sessionMap[sock]->CloseClient();
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

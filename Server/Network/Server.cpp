#include "Server.h"
#include "Timeval.h"
#include "Error.h"

#include "TcpSession.h"


void Server::_InitWSA()
{
	if (WSAStartup(MAKEWORD(2, 2), &_wsaData) != 0)
		ErrorHandling("WSAStartup() error");
}

void Server::_SettingServer()
{
	CheckNullPtr((void*)_port);

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

		for (int i = 0; i < static_cast<int>(_reads.fd_count); i++)
		{
			SOCKET sock = _reads.fd_array[i];

			if (FD_ISSET(sock, &_cpyReads))			//�̺�Ʈ�� �߻��� ������ �ִٸ� true
			{
				if (sock == _hServSock)				//�ش� ������ ���������̶��
					_session = new TcpSession(&_roomManager, &_userMap, _hServSock, &_reads); //TODO : delete�� ���?

				else				//�ش� ������ Ŭ���̾�Ʈ �����̶��
					_userMap[sock]->RecvClient();
			}
		}
	}

}

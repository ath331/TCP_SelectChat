#include "Server.h"
#include "Timeval.h"
#include "Basic.h"

#include "TcpSession.h"

char* defaultPort = "9999";

void Server::_InitWSA()
{
	if (WSAStartup(MAKEWORD(2, 2), &_wsaData) != 0)
		ErrorHandling("WSAStartup() error");
}

void Server::_SettingServer()
{
	if (IsCheckNullPtr(_port))
	{
		_port = defaultPort;
	}

	_InitServerSock();

	_Bind();
	_Listen();

	std::cout << "Server Port : " << defaultPort << std::endl;
}

void Server::_InitServerSock()
{
	_hServSock = socket(PF_INET, SOCK_STREAM, 0);

	ULONG isNonBlocking = 1;
	ioctlsocket(_hServSock,  FIONBIO,  &isNonBlocking); //non-blocking 소켓으로 변경

	memset(&_servAdr, 0, sizeof(_servAdr));
	_servAdr.sin_family = AF_INET;
	_servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	_servAdr.sin_port = htons(static_cast<u_short>(stoi(_port)));
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

	std::cout << "Server Run" << std::endl;

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

			if (FD_ISSET(sock, &_cpyReads))			//이벤트가 발생한 소켓이 있다면 true
			{
				if (sock == _hServSock)				//해당 소켓이 서버소켓이라면
					_session = new TcpSession(&_roomManager, &_userMap, _hServSock, &_reads); //TODO : delete는 어디서?

				else				//해당 소켓이 클라이언트 소켓이라면
					_userMap[sock]->RecvClient();
			}
		}
	}

}

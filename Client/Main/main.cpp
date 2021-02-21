#include <iostream>
#include <stdlib.h>
#include <string>
#include <WinSock2.h>

using namespace std;
#define BUF_SIZE 1024

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	char message[BUF_SIZE];
	int strLen = 0;

	SOCKADDR_IN servAdr, clntAdr;
	int clntAdrSize = 0;

	if (argc != 2)
	{
		cout << "Usage : " << argv[0] << " <port>" << endl;
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cout << "WSAStartup() error" << endl;
		exit(1);
	}

	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET)
	{
		cout << "socket() error" << endl;
		exit(1);
	}

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(atoi(argv[1]));

	if (bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
	{
		cout << "bind() error" << endl;
		exit(1);
	}

	if (listen(hServSock, 5) == SOCKET_ERROR)
	{
		cout << "listen() error" << endl;
		exit(1);
	}

	clntAdrSize = sizeof(clntAdr);

	for (int i = 0; i < 5; i++)
	{
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSize);
		if (hClntSock == -1)
		{
			cout << "accept() error" << endl;
			exit(1);
		}
		else
		{
			cout << "connect client : " << i + 1 << endl;
		}

		while ((strLen = recv(hClntSock, message, BUF_SIZE, 0)) != 0)
		{
			send(hClntSock, message, strLen, 0);
		}

	}

	closesocket(hServSock);
	WSACleanup();

	return 0;
}
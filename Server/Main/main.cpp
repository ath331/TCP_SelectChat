#include <iostream>
#include <string>
#include <WinSock2.h>

using namespace std;
#define BUF_SIZE 1024

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAdr, clntAdr;
	TIMEVAL timeout;
	fd_set reads, cpyReads;

	int adrSz = 0;
	int strLen = 0, fdnum = 0;
	char buf[BUF_SIZE];

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
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(atoi(argv[1]));

	if(bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
	{
		cout << "bind() error" << endl;
		exit(1);
	}

	if(listen(hServSock,5) == SOCKET_ERROR)
	{
		cout << "listen() error" << endl;
		exit(1);
	}

	FD_ZERO(&reads);
	FD_SET(hServSock, &reads);

	while (true)
	{
		cpyReads = reads;
		timeout.tv_sec = 5;
		timeout.tv_usec = 5000;

		if ((fdnum = select(0, &cpyReads, 0, 0, &timeout)) == SOCKET_ERROR)
			break;

		if (fdnum == 0)
			continue;

		for (int i = 0; i < reads.fd_count; i++)
		{
			if (FD_ISSET(reads.fd_array[i], &cpyReads))
			{
				if (reads.fd_array[i] == hServSock)
				{
					adrSz = sizeof(clntAdr);
					hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &adrSz);
					FD_SET(hClntSock, &reads);
					cout << "connected clinet : " << hClntSock << endl;
				}
				else
				{
					strLen = recv(reads.fd_array[i], buf, BUF_SIZE - 1, 0);
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

	closesocket(hServSock);
	WSACleanup();

	return 0;
}
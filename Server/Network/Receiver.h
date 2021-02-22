#pragma once
#include "TcpSession.h"
#include <WinSock2.h>

#define BUF_SIZE 1024

class Receiver
{
public:
	Receiver(SOCKET sock);
	~Receiver();

	SOCKET clntSock;

	void Recv();
private:
	char buf[BUF_SIZE];		//�����͸� �޴� ����
	char cpyBuf[BUF_SIZE];	//���� �����Ͱ� ���̴� ���� -> ���๮��("\n")�� ������ �׿��ִ� �����͸� ��Ŷȭ �Ͽ� �ؼ��Ѵ�.

	int _strLen		= 0;		//�����ֱٿ� ���� �������� ����
	int _cpyStrLen	= 0;		//�׿��ִ� �������� ����

public:
	friend TcpSession;
};


	#pragma once
#include "TcpSession.h"
#include "StringSpliter.h"

#include <WinSock2.h>

#define BUF_SIZE 1

class StringSpliter;
class Receiver
{
public:
	Receiver(SOCKET sock);
	~Receiver();

	SOCKET clntSock;

	void Recv();
	string split();
private:
	StringSpliter* _spliter;					//_bufStr�� �ؼ��ϴ� ��ü.

	char _buf[BUF_SIZE] = { NULL, };			//�����͸� �޴� ����.Telnet�� 1Byte�� �����Ƿ� 10ũ��ε� ����ҵ�?
	string _bufStr;								//���� �����Ͱ� ���̴� ���� -> ���๮��("\n")�� ������ �׿��ִ� �����͸� ��Ŷȭ �Ͽ� �ؼ��Ѵ�.

	int _strLen		= 0;						//���� �ֱٿ� ���� �������� ����

private:
	void InputBackSpace();						//�� �����̽��� �ԷµǾ��� ��

public:
	friend TcpSession;
};


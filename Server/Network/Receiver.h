	#pragma once
#include "TcpSession.h"
#include <string>
//#include "StringSpliter.h"

#include <WinSock2.h>

#define BUF_SIZE 1024

class StringSpliter;
class Receiver
{
public:
	Receiver(SOCKET sock)
		:clntSock(sock), _bufSIze(BUF_SIZE)
	{
		_bufStr = new char[_bufSIze];
	}
	~Receiver()
	{
		if (_bufStr != nullptr)
			delete[] _bufStr;
	}

	SOCKET clntSock;

	void Recv();
	int recvLen = 0;								//���� ������ ����
	std::string split(int pos);						//_bufStr���� pos���� �Ľ��ؼ� string���� ����
private:
	//StringSpliter* _spliter;					//���ۿ��� "\n"�� �ִ��� �˻��ϴ� ��ü

	int _bufSIze = 0;							//������ �ִ�ũ��	
	char* _bufStr;						//���� �����Ͱ� ���̴� ���� -> ���๮��("\n")�� ������ �׿��ִ� �����͸� ��Ŷȭ �Ͽ� �ؼ��Ѵ�.

	int _bufLen	= 0;						//���ۿ� ����Ǿ��ִ� �������� ���� BUF_SIZE�� �ʰ��ϴ� �����Ͱ� ���´ٸ� ���� ���Ҵ� �ʿ�
	int _offSet	= 0;						//���۸� �о���ϴ� ��ġ

private:
	int _FIndEnterCharIndex();					//���ۿ��� '\n'�� ã�Ƽ� �ε����� ��ȯ�ϴ� �Լ�. ã�� ���Ѵٸ� -1�� ��ȯ.
	void _InputBackSpace();						//�� �����̽��� �ԷµǾ��� ��

public:
	friend TcpSession;
};


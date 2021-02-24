#pragma once
#include "TcpSession.h"

#include <WinSock2.h>

class Sender
{
public:
	Sender(SOCKET sock);
	~Sender();


private:
	SOCKET _sock;

private:
	void _Send(const char* buf);	//_sock���� buf�� ����
	void _SendLogin();				//Login�� �ʿ��� �޽����� ����
	void _SendLogined();			//Login�� �Ϸ� �Ǿ��� ���� �޽����� ����
	void _SendCL();					//��ɾ� ����� �����ִ� �޽��� ����
	void _SendMR();					//���� ����� �޽��� ����
	void _SendRL();					//����� ����� �����ִ� �޽��� ����
	void _SendRE();					//�濡 ���� �޽��� ����
	void _SendTO();					//�ӼӸ� �޽��� ����
	void _SendUL();					//�������� ���� ����Ʈ�� �����ִ� �޽��� ����
public:
	friend TcpSession;
};


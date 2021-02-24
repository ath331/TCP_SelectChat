#pragma once
#include "TcpSession.h"

#include <WinSock2.h>

class Sender
{
public:
	Sender();
	~Sender();

	void SendEnter(SOCKET sock);

private:
	void _Send(SOCKET sock, const char* buf);	//_sock���� buf�� ����
	void _SendLogin(SOCKET sock);				//Login�� �ʿ��� �޽����� ����
	void _SendLogined(SOCKET sock);				//Login�� �Ϸ� �Ǿ��� ���� �޽����� ����
	void _SendCL(SOCKET sock);					//��ɾ� ����� �����ִ� �޽��� ����
	void _SendMR(SOCKET sock);					//���� ����� �޽��� ����
	void _SendRL(SOCKET sock);					//����� ����� �����ִ� �޽��� ����
	void _SendRE(SOCKET sock);					//�濡 ���� �޽��� ����
	void _SendUL(SOCKET sock);					//�������� ���� ����Ʈ�� �����ִ� �޽��� ����
	void _SendRI(SOCKET sock);					//���� ������ �����ִ� �޽��� ����
	void _SendRUI(SOCKET sock);					//���� ������ ���̵� ������ �޽��� ����
public:
	friend TcpSession;
};


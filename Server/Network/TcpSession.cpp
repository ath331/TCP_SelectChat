#include "TcpSession.h"

#include "Accepter.h"
#include "Receiver.h"
#include "Sender.h"

#include <WinSock2.h>
#include <iostream>

TcpSession::TcpSession(map<SOCKET, UserState>* userMap, SOCKET sock, fd_set* reads)
	: _reads(reads), _userMap(userMap)
{
	_accept = new Accepter(sock, reads);
	_Accept();

	_receiver = new Receiver(hClntSock);

	_sender = new Sender(hClntSock);
	_sender->_SendLogin();
}


TcpSession::~TcpSession()
{
	delete _accept;
	delete _receiver;
	delete _sender;
}

void TcpSession::_Accept()
{
	_accept->AcceptClient();
	hClntSock = _accept->_GetClntSock();

	UserState userState(this);
	_userMap->insert(make_pair(hClntSock, userState));
}

void TcpSession::RecvClient()
{
	_receiver->Recv();

	if (_receiver->_strLen == 0)
		_CloseClient();

	else if (_receiver->_buf[_receiver->_strLen - 1] == '\n')  //�Էµ��� �������� ���� ������ ���ڰ� ���๮���� ��
	{
		std::string str = _receiver->split();
		_IsCommands(str);
	}
}

void TcpSession::_IsCommands(string str)
{
	bool b = _stringDistinguisher.IsCommands(str);

	if (b)		//str�� ��ɾ��� ������ ó��
	{
		COMMANDS commands = _stringDistinguisher.WhatCommands(str);
		_ProcessingCommands(commands);
	}

	else		//str�� ��ɾ �ƴ϶�� (ä���̶��) �ش� Ŭ���� ���ȣ�� ä�� ����
	{
		std::cout << "[ " << hClntSock<< " ] " << str << std::endl;
	}
}

void TcpSession::_ProcessingCommands(COMMANDS commands)
{
	switch (commands)
	{
	case COMMANDS::LOGIN:
		std::cout << hClntSock << " is Login" << std::endl;
		_sender->_SendLogined();
		break;
	case COMMANDS::CL:
		_sender->_SendCL();
		break;
	case COMMANDS::ENUM_COMMANDS_MAX_COUNT:
		break;
	default:
		break;
	}
}

void TcpSession::_CloseClient()
{
	FD_CLR(hClntSock, _reads);
	closesocket(hClntSock);

	std::cout << "close clinet : " << hClntSock << std::endl;
}


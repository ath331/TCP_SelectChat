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

	else if (_receiver->_buf[_receiver->_strLen - 1] == '\n')  //입력들어온 데이터의 가장 마지막 문자가 개행문자일 때
	{
		std::string str = _receiver->split();
		_IsCommands(str);
	}
}

void TcpSession::_IsCommands(string str)
{
	bool b = _stringDistinguisher.IsCommands(str);

	if (b)		//str이 명령어라면 적절한 처리
	{
		COMMANDS commands = _stringDistinguisher.WhatCommands(str);
		_ProcessingCommands(commands, str);
	}

	else		//str이 명령어가 아니라면 (채팅이라면) 해당 클라의 방번호로 채팅 전송
	{
	}
}

void TcpSession::_ProcessingCommands(COMMANDS commands, string str)
{
	if (commands == COMMANDS::LOGIN && us.GetLoginState() == false)  //명령어가 LOGIN이면서 로그인한 상태가 아니라면
	{
		if (_stringDistinguisher.v.size() > 1) //함수화 하기
			us.setID(_stringDistinguisher.v[1]);

		_sender->_SendLogined();
		us.SetLoginState(true);

		std::cout << "[ " << us.GetID() << " ] " << str << endl;

	}

	if (us.GetID() == "")  //유저정보가 등록되어 있지 않다면 바로 리턴.
		return;

	if (commands != COMMANDS::LOGIN && us.GetLoginState() == true)	//명령어가 LOGIN가 아니고 로그인한 상태라면 다른 명령어를 분기처리한다.
	{
		switch (commands)
		{
		case COMMANDS::CL:
			_sender->_SendCL();
			break;
		default:
			break;
		}

		std::cout << "[ " << us.GetID() << " ] " << str << endl;

	}
}

void TcpSession::_CloseClient()
{
	FD_CLR(hClntSock, _reads);
	closesocket(hClntSock);

	std::cout << "close clinet : " << hClntSock << std::endl;
}


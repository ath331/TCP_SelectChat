#include "TcpSession.h"
#include "RoomManager.h"

#include "Accepter.h"
#include "Receiver.h"
#include "Sender.h"

#include <WinSock2.h>
#include <iostream>

TcpSession::TcpSession(RoomManager* roomManager, map<SOCKET, UserState>* userMap, SOCKET sock, fd_set* reads)
	: _reads(reads), _roomManager(roomManager), _userMap(userMap)
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
		if (_stringDistinguisher.v.size() <= 1) //LOGIN명령어인데 매개변수 없이 입력한 경우는 리턴.
			return;

		if (_stringDistinguisher.v.size() > 1)
			us.setID(_stringDistinguisher.v[1]);

		_sender->_SendLogined();
		us.SetLoginState(true);

		std::cout << "[ " << us.GetID() << " ] " << str << endl;

	}

	if (us.GetID() == "")  //유저정보가 등록되어 있지 않다면 바로 리턴.
		return;

	if (commands != COMMANDS::LOGIN && us.GetLoginState() == true)	//명령어가 LOGIN이 아니고 로그인한 상태라면 다른 명령어를 분기처리한다.
	{
		//TODO : 명령어들별로 함수화 시키기
		switch (commands)
		{
		case COMMANDS::CL: //CommandsList
			_sender->_SendCL();
			break;

		case COMMANDS::MR: //MakeRoom
			if (_stringDistinguisher.v.size() > 3) //비공개방 생성
			{
				_roomManager->MakeRoom(_stringDistinguisher.v[1], stoi(_stringDistinguisher.v[2]), stoi(_stringDistinguisher.v[3]));
				_sender->_SendMR();
			}
			else if (_stringDistinguisher.v.size() == 3) //공개방 생성
			{
				_roomManager->MakeRoom(_stringDistinguisher.v[1], stoi(_stringDistinguisher.v[2]));
				_sender->_SendMR();
			}
			break;

		case COMMANDS::RE: //RoomEnter
			_sender->_SendRE();
			break;

		case COMMANDS::RL: //RoomList
			_sender->_SendRL();
			for (auto i : _roomManager->_roomMap)
			{
				auto roomInfo = i.second;
				string roomInfoStr;
				roomInfoStr = (to_string(roomInfo.roomNum) + "\t\t" + roomInfo.name + "\t\t" + to_string(roomInfo.userRoomMap.size()) + "/" + to_string(roomInfo.maxUserCount) + "\t\t");
				if (roomInfo.isPrivateRoom)
					roomInfoStr += "True";
				else
					roomInfoStr += "False";

				_sender->_Send(roomInfoStr.c_str());
				_sender->SendEnter();
			}
			break;

		case COMMANDS::TO: //To
			_sender->_SendTO();
			break;

		case COMMANDS::UL: //UserList
			_sender->_SendUL();
			break;

		default:
			return;   //올바르지 않은 명령어가 들어오면 바로 리턴.
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


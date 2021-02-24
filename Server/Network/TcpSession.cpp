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
		_ProcessingCommands(commands, str);
	}

	else		//str�� ��ɾ �ƴ϶�� (ä���̶��) �ش� Ŭ���� ���ȣ�� ä�� ����
	{
	}
}

void TcpSession::_ProcessingCommands(COMMANDS commands, string str)
{
	if (commands == COMMANDS::LOGIN && us.GetLoginState() == false)  //��ɾ LOGIN�̸鼭 �α����� ���°� �ƴ϶��
	{
		if (_stringDistinguisher.v.size() <= 1) //LOGIN��ɾ��ε� �Ű����� ���� �Է��� ���� ����.
			return;

		if (_stringDistinguisher.v.size() > 1)
			us.setID(_stringDistinguisher.v[1]);

		_sender->_SendLogined();
		us.SetLoginState(true);

		std::cout << "[ " << us.GetID() << " ] " << str << endl;

	}

	if (us.GetID() == "")  //���������� ��ϵǾ� ���� �ʴٸ� �ٷ� ����.
		return;

	if (commands != COMMANDS::LOGIN && us.GetLoginState() == true)	//��ɾ LOGIN�� �ƴϰ� �α����� ���¶�� �ٸ� ��ɾ �б�ó���Ѵ�.
	{
		//TODO : ��ɾ�麰�� �Լ�ȭ ��Ű��
		switch (commands)
		{
		case COMMANDS::CL: //CommandsList
			_sender->_SendCL();
			break;

		case COMMANDS::MR: //MakeRoom
			if (_stringDistinguisher.v.size() > 3) //������� ����
			{
				_roomManager->MakeRoom(_stringDistinguisher.v[1], stoi(_stringDistinguisher.v[2]), stoi(_stringDistinguisher.v[3]));
				_sender->_SendMR();
			}
			else if (_stringDistinguisher.v.size() == 3) //������ ����
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
			return;   //�ùٸ��� ���� ��ɾ ������ �ٷ� ����.
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


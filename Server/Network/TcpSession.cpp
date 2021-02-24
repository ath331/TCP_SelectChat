#include "TcpSession.h"
#include "RoomManager.h"

#include "Accepter.h"
#include "Receiver.h"
#include "Sender.h"

#include <WinSock2.h>
#include <iostream>

TcpSession::TcpSession(RoomManager* roomManager, map<SOCKET, TcpSession*>* userMap, SOCKET sock, fd_set* reads)
	: _reads(reads), _roomManager(roomManager), _userMap(userMap)
{
	_accept = new Accepter(sock, reads);
	_Accept();

	_receiver = new Receiver(hClntSock);

	_sender = new Sender();
	_sender->_SendLogin(hClntSock);
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

	us.hClntSock = hClntSock;
	_userMap->insert(make_pair(hClntSock, this));
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

	else		//str�� ��ɾ �ƴ϶�� (ä���̶��) �ش� Ŭ���� ���ȣ�� ä�� ����. �κ��ִٸ� �κ�� ä�� ����
	{
		_ProcessingChatting(str);
	}
}

void TcpSession::_ProcessingChatting(string str)
{
	if (us.GetLoginState() == false) //�α������� ���� ���¶�� �����Ѵ�
		return;

	string message = ( "[ " + us.GetID() + " ]");
	message += (" " + str);

	if (us.GetIsEnteredRoom() == false) //�κ񿡼� ä���� �Է��ߴٸ�
	{
#define SESSION iter->second
		for (auto iter = _userMap->begin(); iter != _userMap->end(); iter++)
		{
			if (SESSION->us.GetIsEnteredRoom() == false) //�κ� �ִ� ������ Ž��
			{
				SOCKET sock = SESSION->hClntSock;
				_sender->_Send(sock, message.c_str());
				_sender->SendEnter(sock); //�޽����� ������ ����ó���Ѵ�
			}
		}
	}

	else if (us.GetIsEnteredRoom() == true) //�濡�� ä���� �Է��ߴٸ�
	{
#define USER iter->second
		for (auto iter = _roomManager->_roomMap.begin(); iter != _roomManager->_roomMap.end(); iter++) //�ش� ���� ã�Ƽ�
		{
#define ROOM iter->second
			if (ROOM.roomNum == us.GetRoomNum())
			{
				for (auto userStateIter = ROOM.userRoomMap.begin(); userStateIter != ROOM.userRoomMap.end(); userStateIter++) //�濡 �ִ� ��� �������� �޽��� ����
				{
					_sender->_Send(userStateIter->second.hClntSock, message.c_str());
					_sender->SendEnter(userStateIter->second.hClntSock); //�޽����� ������ ����ó���Ѵ�

				}
				break;
			}
		}
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

		_sender->_SendLogined(hClntSock);
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
			_sender->_SendCL(hClntSock);
			break;

		case COMMANDS::MR: //MakeRoom
		{
			if (us.GetIsEnteredRoom() == true) //�̹� �濡 �������̶�� ��ɾ� ����
				return;

			string enterStr;
			if (_stringDistinguisher.v.size() > 3) //������� ����
			{
				_roomManager->MakeRoom(_stringDistinguisher.v[1], stoi(_stringDistinguisher.v[2]), stoi(_stringDistinguisher.v[3]));
				_sender->_SendMR(hClntSock);
				if (_roomManager->EnterRoom(_roomManager->nextRoomNum - 1, us, stoi(_stringDistinguisher.v[3])) == true) //��� ���� �濡 �����ϱ� ���� -1�� ������ ����. _roomManager->nextRoomNum-1
				{
					_sender->_SendRE(hClntSock);
				}
			}
			else if (_stringDistinguisher.v.size() == 3) //������ ����
			{
				_roomManager->MakeRoom(_stringDistinguisher.v[1], stoi(_stringDistinguisher.v[2]));
				_sender->_SendMR(hClntSock);
				if (_roomManager->EnterRoom(_roomManager->nextRoomNum - 1, us) == true) //��� ���� �濡 �����ϱ� ���� -1�� ������ ����. _roomManager->nextRoomNum-1
				{
					_sender->_SendRE(hClntSock);
				}
			}

			_ProcessingCommands(COMMANDS::RE, enterStr);

			break;
		}

		case COMMANDS::RE: //RoomEnter
		{
			if (us.GetIsEnteredRoom() == true) //�̹� �濡 �������̶�� ��ɾ� ����
				return;

			if (_stringDistinguisher.v.size() < 2) //�����Ϸ��� ���� ������ �Է����� ������ break
				break;

			int password = 0;
			int roomNum = stoi(_stringDistinguisher.v[1]); //TODO : string, int �����ϱ�
			if (_stringDistinguisher.v.size() > 2) //��й�ȣ���� ���� �Է��ߴٸ� true (������ �����ε� ��й�ȣ�� �Է��߾ ���尡��)
				password = stoi(_stringDistinguisher.v[2]);

			if (_roomManager->EnterRoom(roomNum, us, password) == true) //�� ���� ����
			{
				_sender->_SendRE(hClntSock);
			}

			else
				_sender->_Send(hClntSock, "���� ����.");

			break;
		}

		case COMMANDS::RL: //RoomList
			_sender->_SendRL(hClntSock);
			for (auto i : _roomManager->_roomMap)
			{
				auto roomInfo = i.second;
				string roomInfoStr;
				roomInfoStr = (to_string(roomInfo.roomNum) + "\t\t" + roomInfo.name + "\t\t" + to_string(roomInfo.userRoomMap.size()) + "/" + to_string(roomInfo.maxUserCount) + "\t\t");
				if (roomInfo.isPrivateRoom)
					roomInfoStr += "True";
				else
					roomInfoStr += "False";

				_sender->_Send(hClntSock, roomInfoStr.c_str());
				_sender->SendEnter(hClntSock);
			}
			break;

		case COMMANDS::TO: //To
		{
			if (_stringDistinguisher.v.size() < 3) //�ӼӸ��� �޴� ����� ���̵�, �ӼӸ��� ������� ��� ��ɾ�� �Է����� �ʾ����� break
			{
				_sender->_Send(hClntSock, "������ �Է��ϼ���.\r\n");
				break;
			}

			SOCKET senderSock = hClntSock; //������ ���
			SOCKET receiverSock;		   //�޴� ���
			string senderID;
			string receiverID = _stringDistinguisher.v[1];
			for (auto iter = _userMap->begin(); iter != _userMap->end(); iter++)
			{
				if (iter->second->us.GetID() == receiverID)
				{
					receiverSock = iter->second->us.hClntSock;
					string message;
					for (int i = 2; i < _stringDistinguisher.v.size(); i++)
						message += _stringDistinguisher.v[i];

					message = ("[�ӼӸ�] " + us.GetID() + " : " + message);
					_sender->_Send(receiverSock, message.c_str());
					_sender->_Send(receiverSock, "\r\n");

					return;;
				}
			}
			_sender->_Send(hClntSock, "�������� ���� ID �Դϴ�.\r\n");
			break;
		}

		case COMMANDS::UL: //UserList
			_sender->_SendUL(hClntSock);
			break;

		case COMMANDS::Q:
			if (us.GetIsEnteredRoom() == false)
				return;

			_roomManager->OutRoom(us.GetRoomNum(), us);
			_sender->_SendLogined(hClntSock);

			break;
		case COMMANDS::QUIT:
			break;
		case COMMANDS::RI:
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


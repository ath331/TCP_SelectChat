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

	_userState.hClntSock = hClntSock;
	_userMap->insert(make_pair(hClntSock, this));
}

void TcpSession::RecvClient()
{
	_receiver->Recv();

	if (_receiver->_strLen == 0)
		_CloseClient();

	else if (_receiver->_buf[_receiver->_strLen - 1] == '\b')//�Էµ��� �������� ���� ������ ���ڰ� �� �����̽��� ��
	{
		_receiver->InputBackSpace();
		_sender->_Send(hClntSock, " ");
		_sender->_Send(hClntSock, "\b");
	}

	else if (_receiver->_buf[_receiver->_strLen - 1] == '\n')  //�Էµ��� �������� ���� ������ ���ڰ� ���๮���� ��
	{
		std::string str = _receiver->split();
		_IsCommands(str);
	}
}

void TcpSession::_IsCommands(string& str)
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
	if (_userState.GetLoginState() == false) //�α������� ���� ���¶�� �����Ѵ�
		return;

	string message = ("[ " + _userState.GetID() + " ]");
	message += (" " + str);

	if (_userState.GetIsEnteredRoom() == false) //�κ񿡼� ä���� �Է��ߴٸ�
	{
#define SESSION iter->second
		for (auto iter = _userMap->begin(); iter != _userMap->end(); iter++)
		{
			if (SESSION->_userState.GetIsEnteredRoom() == false) //�κ� �ִ� ������ Ž��
			{
				SOCKET sock = SESSION->hClntSock;
				_sender->_Send(sock, message.c_str());
				_sender->SendEnter(sock); //�޽����� ������ ����ó���Ѵ�
			}
		}
	}

	else if (_userState.GetIsEnteredRoom() == true) //�濡�� ä���� �Է��ߴٸ�
	{
		for (auto iter = _roomManager->_roomMap.begin(); iter != _roomManager->_roomMap.end(); iter++) //�ش� ���� ã�Ƽ�
		{
#define ROOM iter->second
			if (ROOM.roomNum == _userState.GetRoomNum())
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
	if (commands == COMMANDS::LOGIN && _userState.GetLoginState() == false)  //��ɾ LOGIN�̸鼭 �α����� ���°� �ƴ϶��
	{
		if (COMMANDS_PARAMETERS_VECTOR.size() <= NONE_LOGIN_PARAMETERS) //LOGIN��ɾ��ε� �Ű����� ���� �Է��� ���� ����.
			return;

		if (COMMANDS_PARAMETERS_VECTOR.size() > NONE_LOGIN_PARAMETERS)
			_userState.setID(LOGIN_ID);

		_sender->_SendLogined(hClntSock);
		_userState.SetLoginState(true);

		std::cout << "[ " << _userState.GetID() << " ] " << str << endl;

	}

	if (_userState.GetID() == "")  //���������� ��ϵǾ� ���� �ʴٸ� �ٷ� ����.
		return;

	if (commands != COMMANDS::LOGIN && _userState.GetLoginState() == true)	//��ɾ LOGIN�� �ƴϰ� �α����� ���¶�� �ٸ� ��ɾ �б�ó���Ѵ�.
	{
		//TODO : ��ɾ�麰�� �Լ�ȭ ��Ű��
		switch (commands)
		{
		case COMMANDS::CL: //CommandsList
			_sender->_SendCL(hClntSock);
			break;

		case COMMANDS::MR: //MakeRoom
		{
			if (_userState.GetIsEnteredRoom() == true) //�̹� �濡 �������̶�� ��ɾ� ����
				return;

			if (COMMANDS_PARAMETERS_VECTOR.size() > MAKE_ROOM_PARAMETERS_COUNTS) //������� ����
			{
				_roomManager->MakeRoom(ROOM_NAME, stoi(_stringDistinguisher.commandsParametersListVec[2]), MAKE_ROOM_PASSWORD);
				if (_roomManager->EnterRoom(_roomManager->nextRoomNum - 1, _userState, MAKE_ROOM_PASSWORD) == true) //��� ���� �濡 �����ϱ� ���� -1�� ������ ����. _roomManager->nextRoomNum-1
				{
					_sender->_SendRE(hClntSock);
				}
			}
			else if (COMMANDS_PARAMETERS_VECTOR.size() == MAKE_ROOM_PARAMETERS_COUNTS) //������ ����
			{
				_roomManager->MakeRoom(ROOM_NAME, stoi(_stringDistinguisher.commandsParametersListVec[2]));
				if (_roomManager->EnterRoom(_roomManager->nextRoomNum - 1, _userState) == true) //��� ���� �濡 �����ϱ� ���� -1�� ������ ����. _roomManager->nextRoomNum-1
				{
					_sender->_SendRE(hClntSock);
				}
			}

			break;
		}

		case COMMANDS::RE: //RoomEnter
		{
			if (_userState.GetIsEnteredRoom() == true) //�̹� �濡 �������̶�� ��ɾ� ����
				return;

			if (COMMANDS_PARAMETERS_VECTOR.size() < NONE_ENTER_ROOM_PARAMETERS) //�����Ϸ��� ���� ������ �Է����� ������ break
				break;

			string password;
			int roomNum = stoi(_stringDistinguisher.commandsParametersListVec[1]);
			if (COMMANDS_PARAMETERS_VECTOR.size() > NONE_ENTER_ROOM_PARAMETERS) //��й�ȣ���� ���� �Է��ߴٸ� true (������ �����ε� ��й�ȣ�� �Է��߾ ���尡��)
				password = ENTER_ROOM_PASSWORD;

			if (_roomManager->EnterRoom(roomNum, _userState, password) == true) //�� ���� ����
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
			if (COMMANDS_PARAMETERS_VECTOR.size() < TO_PARAMETERS_COUNTS) //�ӼӸ��� �޴� ����� ���̵�, �ӼӸ��� ������� ��� ��ɾ�� �Է����� �ʾ����� break
			{
				_sender->_Send(hClntSock, "������ �Է��ϼ���.\r\n");
				break;
			}

			SOCKET senderSock = hClntSock; //������ ���
			SOCKET receiverSock;		   //�޴� ���
			string senderID;
			string receiverID = RECEIVER_ID;
			for (auto iter = _userMap->begin(); iter != _userMap->end(); iter++)
			{
				if (iter->second->_userState.GetID() == receiverID)
				{
					receiverSock = iter->second->_userState.hClntSock;
					string message;
					for (int i = 2; i < COMMANDS_PARAMETERS_VECTOR.size(); i++)
						message += COMMANDS_PARAMETERS_VECTOR[i];

					message = ("[�ӼӸ�] " + _userState.GetID() + " : " + message);
					_sender->_Send(receiverSock, message.c_str());
					_sender->_Send(receiverSock, "\r\n");

					return;;
				}
			}
			_sender->_Send(hClntSock, "�������� ���� ID �Դϴ�.\r\n");
			break;
		}

		case COMMANDS::UL: //UserList
		{
#define USER_STATE iter->second->_userState
			_sender->_SendUL(hClntSock);
			for (auto iter = _userMap->begin(); iter != _userMap->end(); iter++)
			{
				string userInfo = USER_STATE.GetID() + "\t\t" + to_string(USER_STATE.GetRoomNum());
				_sender->_Send(hClntSock, userInfo.c_str());
				_sender->SendEnter(hClntSock);
			}
			_sender->SendEnter(hClntSock);
			break;
		}

		case COMMANDS::Q:
			if (_userState.GetIsEnteredRoom() == false)
				return;

			_roomManager->OutRoom(_userState.GetRoomNum(), _userState);
			_sender->_SendLogined(hClntSock);

			break;
		case COMMANDS::QUIT:
			_CloseClient();
			break;
		case COMMANDS::RI:
		{
			if (_userState.GetIsEnteredRoom() == false) //�κ񿡼� RoomInfo��ɾ ȣ���ϸ� �����Ѵ�.
				break;

			_sender->_SendRI(hClntSock);

#define ROOM _roomManager->_roomMap[_userState.GetRoomNum()] //user�� �����ϴ� room ����
			string message;
			message += (to_string(ROOM.roomNum) + "\t\t" + ROOM.name + "\t" + to_string(ROOM.userRoomMap.size()) + " / " + to_string(ROOM.maxUserCount));
			_sender->_Send(hClntSock, message.c_str());
			_sender->SendEnter(hClntSock);
			_sender->_SendRUI(hClntSock);

#define MAX_PRINT_USER_ID_COUNT 5 //�� �ٿ� �ִ� ������ ǥ�����ٰ����� ���Ѵ�
			string userID;
			int userCount = 0;
			for (auto iter = ROOM.userRoomMap.begin(); iter != ROOM.userRoomMap.end(); iter++) //�ش�濡 �ִ� ��� ������ ���̵� ���� ���� �ݺ���
			{
				userID += iter->second.GetID() + " ";
				userCount++;
				if (userCount % MAX_PRINT_USER_ID_COUNT == 0) 
					userID += "\r\n";
			}
			_sender->_Send(hClntSock, userID.c_str());
			_sender->SendEnter(hClntSock);

			break;
		}

		default:
			return;   //�ùٸ��� ���� ��ɾ ������ �ٷ� ����.
		}

		std::cout << "[ " << _userState.GetID() << " ] " << str << endl;

	}
}

void TcpSession::_CloseClient()
{
	_userMap->erase(hClntSock);

	FD_CLR(hClntSock, _reads);
	closesocket(hClntSock);

	std::cout << "close clinet : " << hClntSock << std::endl;
}


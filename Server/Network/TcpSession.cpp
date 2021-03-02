#include "TcpSession.h"
#include "RoomManager.h"

#include "Accepter.h"
#include "Receiver.h"
#include "Sender.h"

#include <WinSock2.h>
#include <iostream>

TcpSession::TcpSession(RoomManager* roomManager, unordered_map<SOCKET, TcpSession*>* userMap, SOCKET sock, fd_set* reads)
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

	else if (_receiver->_bufStr == "")
		return;

	else if (_receiver->_buf[_receiver->_strLen - 1] == '\b')//�Էµ��� �������� ���� ������ ���ڰ� �� �����̽��� ��
	{
		_receiver->InputBackSpace();
		_sender->_Send(hClntSock, " ");
		_sender->_Send(hClntSock, "\b");
	}
	else if (_receiver->_bufStr[_receiver->_bufStr.length() - 1] == '\n')  //�Էµ��� �������� ���� ������ ���ڰ� ���๮���� ��
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
		COMMANDS commands = _stringDistinguisher.WhatCommands(COMMANDS_PARAMETERS_VECTOR[0] + " ");
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

	string message;
	if (_userState.GetIsEnteredRoom() == false) //�κ񿡼��� ä���̶��
	{
		message = ("[ Lobby ] ");
	}
	else if (_userState.GetIsEnteredRoom() == true) //�濡���� ä���̶��
	{
		message = ("[ Room ] ");
	}
	message += "[ " + _userState.GetID() + " ]";
	message += (" " + str);

	if (_userState.GetIsEnteredRoom() == false) //�κ񿡼� ä���� �Է��ߴٸ�
	{
#define SESSION iter->second
		for (auto iter = _userMap->begin(); iter != _userMap->end(); iter++)
		{
			if (SESSION->_userState.GetIsEnteredRoom() == false && SESSION->_userState.GetLoginState() == true) //�κ� �ִ� ������ Ž��
			{
				SOCKET sock = SESSION->hClntSock;
				_sender->_Send(sock, message.c_str());
				_sender->SendEnter(sock); //�޽����� ���๮�ڸ� �����Ѵ�
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
		{
			_sender->_Send(hClntSock, "ID�� �Է��ϼ��� /LOGIN [ ID ]");
			_sender->SendEnter(hClntSock);
			return;
		}

		for (auto iter = _userMap->begin(); iter != _userMap->end(); iter++)
		{
			if (iter->second->_userState.GetID() == LOGIN_ID)
			{
				_sender->_Send(hClntSock, "�������� ID �Դϴ�.");
				_sender->SendEnter(hClntSock);
				return;
			}
		}
#define MAX_ID_LENGTH 5
		if (COMMANDS_PARAMETERS_VECTOR.size() > NONE_LOGIN_PARAMETERS)
		{
			if (LOGIN_ID.length() > MAX_ID_LENGTH)
			{
				_sender->_Send(hClntSock, "ID ���̰� 5�� �ѽ��ϴ�.");
				_sender->SendEnter(hClntSock);
				return;
			}

			_userState.setID(LOGIN_ID);

			_sender->_SendLogined(hClntSock);
			_userState.SetLoginState(true);

			std::cout << "[ " << _userState.GetID() << " ] " << str;
		}

	}

	if (_userState.GetID() == "")  //���������� ��ϵǾ� ���� �ʴٸ� �ٷ� ����.
	{
		_sender->_SendLogin(hClntSock);
		_sender->SendEnter(hClntSock);
		return;
	}

	if (commands != COMMANDS::LOGIN && _userState.GetLoginState() == true)	//��ɾ LOGIN�� �ƴϰ� �α����� ���¶�� �ٸ� ��ɾ �б�ó���Ѵ�.
	{
		switch (commands)
		{
		case COMMANDS::CL: //CommandsList
			_sender->_SendCL(hClntSock);
			break;

		case COMMANDS::MR: //MakeRoom
		{
			if (_userState.GetIsEnteredRoom() == true) //�̹� �濡 �������̶�� ��ɾ� ����
			{
				_sender->_Send(hClntSock, "�̹� �濡 �������Դϴ�.");
				_sender->SendEnter(hClntSock);
				return;
			}

			if (COMMANDS_PARAMETERS_VECTOR.size() < MAKE_ROOM_PARAMETERS_COUNTS)
			{
				_sender->_Send(hClntSock, "���� ������ �Է��ϼ���. /MR [ �� �̸� ] [ �ִ� �ο� ] [ ��й�ȣ (�������� ������ ����) ]");
				_sender->SendEnter(hClntSock);
				break;
			}


			if (COMMANDS_PARAMETERS_VECTOR.size() > MAKE_ROOM_PARAMETERS_COUNTS) //������� ����
			{
				_roomManager->MakeRoom(ROOM_NAME, ROOM_MAX_USER_COUNTS, MAKE_ROOM_PASSWORD);
				if (_roomManager->EnterRoom(_roomManager->nextRoomNum - 1, _userState, MAKE_ROOM_PASSWORD) == true) //��� ���� �濡 �����ϱ� ���� -1�� ������ ����.
				{
					_sender->_SendRE(hClntSock);
				}
			}
			else if (COMMANDS_PARAMETERS_VECTOR.size() == MAKE_ROOM_PARAMETERS_COUNTS) //������ ����
			{
				_roomManager->MakeRoom(ROOM_NAME, ROOM_MAX_USER_COUNTS);
				if (_roomManager->EnterRoom(_roomManager->nextRoomNum - 1, _userState) == true) //��� ���� �濡 �����ϱ� ���� -1�� ������ ����.
				{
					_sender->_SendRE(hClntSock);
				}
			}

			break;
		}

		case COMMANDS::RE: //RoomEnter
		{
			if (_userState.GetIsEnteredRoom() == true) //�̹� �濡 �������̶�� ��ɾ� ����
			{
				_sender->_Send(hClntSock, "�̹� �濡 �������Դϴ�.");
				_sender->SendEnter(hClntSock);
				return;
			}

			if (COMMANDS_PARAMETERS_VECTOR.size() < NONE_ENTER_ROOM_PARAMETERS) //�����Ϸ��� ���� ������ �Է����� ������ break
			{
				_sender->_Send(hClntSock, "�����Ͻ÷��� ���� ������ �Է��ϼ���. /RE [ �� ��ȣ ] [ ��й�ȣ ]");
				_sender->SendEnter(hClntSock);
				break;
			}

			string password;
			int roomNum = stoi(_stringDistinguisher.commandsParametersListVec[1]);
			if (COMMANDS_PARAMETERS_VECTOR.size() > NONE_ENTER_ROOM_PARAMETERS) //��й�ȣ���� ���� �Է��ߴٸ� true (������ �����ε� ��й�ȣ�� �Է��߾ ���尡��)
				password = ENTER_ROOM_PASSWORD;

			if (_roomManager->EnterRoom(roomNum, _userState, password) == true) //�� ���� ����
			{
				_sender->_SendRE(hClntSock);
			}

			else
				_sender->_Send(hClntSock, "���� ����.\r\n");

			break;
		}

		case COMMANDS::RL: //RoomList
		{
			size_t listCount = _roomManager->_roomMap.size()+1;
			string listCountStr = "($" + to_string(listCount);
			_sender->_Send(hClntSock, listCountStr.c_str());
			_sender->SendEnter(hClntSock);

			_sender->_SendRL(hClntSock);
			for (const auto& i : _roomManager->_roomMap)
			{
				const auto& roomInfo = i.second;
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
		}

		case COMMANDS::TO: //To
		{
			if (COMMANDS_PARAMETERS_VECTOR.size() < TO_PARAMETERS_COUNTS - 1) //�ӼӸ��� �޴� ����� ���̵�, �ӼӸ��� ������� ��� ��ɾ�� �Է����� �ʾ����� break
			{
				_sender->_Send(hClntSock, "�޴� ����� ���̵� �Է��ϼ���.\r\n");
				break;
			}

			if (COMMANDS_PARAMETERS_VECTOR.size() < TO_PARAMETERS_COUNTS) //�ӼӸ��� �޴� ����� ���̵�, �ӼӸ��� ������� ��� ��ɾ�� �Է����� �ʾ����� break
			{
				_sender->_Send(hClntSock, "������ �Է��ϼ���.\r\n");
				break;
			}

			SOCKET receiverSock;		   //�޴� ���
			string senderID = _userState.GetID();
			string receiverID = RECEIVER_ID;

#define USER_STATE iter->second->_userState
			for (auto iter = _userMap->begin(); iter != _userMap->end(); iter++)
			{
				if (USER_STATE.GetID() == receiverID)
				{
					receiverSock = USER_STATE.hClntSock;
					string message;
					for (int i = MESSAGE_INDEX; i < COMMANDS_PARAMETERS_VECTOR.size(); i++)
						message += (COMMANDS_PARAMETERS_VECTOR[i] + " ");

					string to = "[ Whisper ] ";
					message = to + "[ " + senderID + " ]" + " : " + message;
					_sender->_Send(receiverSock, message.c_str());
					_sender->_Send(receiverSock, "\r\n");

					return;
				}
			}
			_sender->_Send(hClntSock, "�������� ���� ID �Դϴ�.\r\n");
			break;
		}

		case COMMANDS::UL: //UserList
		{
#define USER_STATE iter->second->_userState
			size_t listCount = _userMap->size() + 1;
			string listCountStr = "(#" + to_string(listCount);
			_sender->_Send(hClntSock, listCountStr.c_str());
			_sender->SendEnter(hClntSock);

			_sender->_SendUL(hClntSock);
			for (auto iter = _userMap->begin(); iter != _userMap->end(); iter++)
			{
				if (iter->second->_userState.GetLoginState() == true)
				{

					string userInfo = USER_STATE.GetID() + "\t\t" + to_string(USER_STATE.GetRoomNum());
					_sender->_Send(hClntSock, userInfo.c_str());
					_sender->SendEnter(hClntSock);
				}
			}
			//_sender->SendEnter(hClntSock);
			break;
		}

		case COMMANDS::Q:
			if (_userState.GetIsEnteredRoom() == false)
				return;

			_roomManager->OutRoom(_userState.GetRoomNum(), _userState);
			_sender->_SendLogined(hClntSock);

			break;
		case COMMANDS::QUIT:
			if (_userState.GetIsEnteredRoom() == true)
				return;

			_CloseClient();
			break;
		case COMMANDS::RI:
		{
			if (_userState.GetIsEnteredRoom() == false) //�κ񿡼� RoomInfo��ɾ ȣ���ϸ� �����Ѵ�.
			{
				_sender->_Send(hClntSock, "�濡 �����ؼ� ����� �� �ִ� ��ɾ� �Դϴ�.");
				_sender->SendEnter(hClntSock);

				break;
			}

			_sender->_SendRI(hClntSock);

#define USER_ROOM _roomManager->_roomMap[_userState.GetRoomNum()] //user�� �����ϴ� room ����
			string message;
			message += (to_string(USER_ROOM.roomNum) + "\t\t" + USER_ROOM.name + "\t" + to_string(USER_ROOM.userRoomMap.size()) + " / " + to_string(USER_ROOM.maxUserCount));
			_sender->_Send(hClntSock, message.c_str());
			_sender->SendEnter(hClntSock);
			_sender->_SendRUI(hClntSock);

#define MAX_PRINT_USER_ID_COUNT 5 //�� �ٿ� �ִ� ������ ǥ�����ٰ����� ���Ѵ�
			string userID;
			int userCount = 0;
			for (auto iter = USER_ROOM.userRoomMap.begin(); iter != USER_ROOM.userRoomMap.end(); iter++) //�ش�濡 �ִ� ��� ������ ���̵� ���� ���� �ݺ���
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
			_sender->_Send(hClntSock, "�ùٸ��� ���� ��ɾ� �Դϴ�. ��ɾ� ���� : /CL");
			_sender->SendEnter(hClntSock);
			return;   //�ùٸ��� ���� ��ɾ ������ �ٷ� ����.
		}

		std::cout << "[ " << _userState.GetID() << " ] " << str << endl;

	}
}

void TcpSession::_CloseClient()
{
	UserState userState;  //������ ������ �� �������̴� �濡�� �ƿ�ó���ϵ��� ����
	for (auto iter = _userMap->begin(); iter != _userMap->end(); iter++)
	{
		if (iter->second->hClntSock == hClntSock)
			userState = iter->second->_userState;
	}

	_roomManager->OutRoom(userState.GetRoomNum(), userState);
	_userMap->erase(hClntSock);

	FD_CLR(hClntSock, _reads);
	closesocket(hClntSock);

	std::cout << "close clinet : " << hClntSock << std::endl;
}


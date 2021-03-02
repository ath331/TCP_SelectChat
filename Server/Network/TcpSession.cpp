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

	else if (_receiver->_buf[_receiver->_strLen - 1] == '\b')//입력들어온 데이터의 가장 마지막 문자가 백 스페이스일 때
	{
		_receiver->InputBackSpace();
		_sender->_Send(hClntSock, " ");
		_sender->_Send(hClntSock, "\b");
	}
	else if (_receiver->_bufStr[_receiver->_bufStr.length() - 1] == '\n')  //입력들어온 데이터의 가장 마지막 문자가 개행문자일 때
	{
		std::string str = _receiver->split();
		_IsCommands(str);
	}
}

void TcpSession::_IsCommands(string& str)
{
	bool b = _stringDistinguisher.IsCommands(str);

	if (b)		//str이 명령어라면 적절한 처리
	{
		COMMANDS commands = _stringDistinguisher.WhatCommands(COMMANDS_PARAMETERS_VECTOR[0] + " ");
		_ProcessingCommands(commands, str);
	}

	else		//str이 명령어가 아니라면 (채팅이라면) 해당 클라의 방번호로 채팅 전송. 로비에있다면 로비로 채팅 전송
	{
		_ProcessingChatting(str);
	}
}

void TcpSession::_ProcessingChatting(string str)
{
	if (_userState.GetLoginState() == false) //로그인하지 않은 상태라면 무시한다
		return;

	string message;
	if (_userState.GetIsEnteredRoom() == false) //로비에서의 채팅이라면
	{
		message = ("[ Lobby ] ");
	}
	else if (_userState.GetIsEnteredRoom() == true) //방에서의 채팅이라면
	{
		message = ("[ Room ] ");
	}
	message += "[ " + _userState.GetID() + " ]";
	message += (" " + str);

	if (_userState.GetIsEnteredRoom() == false) //로비에서 채팅을 입력했다면
	{
#define SESSION iter->second
		for (auto iter = _userMap->begin(); iter != _userMap->end(); iter++)
		{
			if (SESSION->_userState.GetIsEnteredRoom() == false && SESSION->_userState.GetLoginState() == true) //로비에 있는 유저를 탐색
			{
				SOCKET sock = SESSION->hClntSock;
				_sender->_Send(sock, message.c_str());
				_sender->SendEnter(sock); //메시지와 개행문자를 전송한다
			}
		}
	}

	else if (_userState.GetIsEnteredRoom() == true) //방에서 채팅을 입력했다면
	{
		for (auto iter = _roomManager->_roomMap.begin(); iter != _roomManager->_roomMap.end(); iter++) //해당 방을 찾아서
		{
#define ROOM iter->second
			if (ROOM.roomNum == _userState.GetRoomNum())
			{
				for (auto userStateIter = ROOM.userRoomMap.begin(); userStateIter != ROOM.userRoomMap.end(); userStateIter++) //방에 있는 모든 유저에게 메시지 전송
				{
					_sender->_Send(userStateIter->second.hClntSock, message.c_str());
					_sender->SendEnter(userStateIter->second.hClntSock); //메시지를 받으면 개행처리한다

				}
				break;
			}
		}
	}
}

void TcpSession::_ProcessingCommands(COMMANDS commands, string str)
{

	if (commands == COMMANDS::LOGIN && _userState.GetLoginState() == false)  //명령어가 LOGIN이면서 로그인한 상태가 아니라면
	{
		if (COMMANDS_PARAMETERS_VECTOR.size() <= NONE_LOGIN_PARAMETERS) //LOGIN명령어인데 매개변수 없이 입력한 경우는 리턴.
		{
			_sender->_Send(hClntSock, "ID를 입력하세요 /LOGIN [ ID ]");
			_sender->SendEnter(hClntSock);
			return;
		}

		for (auto iter = _userMap->begin(); iter != _userMap->end(); iter++)
		{
			if (iter->second->_userState.GetID() == LOGIN_ID)
			{
				_sender->_Send(hClntSock, "접속중인 ID 입니다.");
				_sender->SendEnter(hClntSock);
				return;
			}
		}
#define MAX_ID_LENGTH 5
		if (COMMANDS_PARAMETERS_VECTOR.size() > NONE_LOGIN_PARAMETERS)
		{
			if (LOGIN_ID.length() > MAX_ID_LENGTH)
			{
				_sender->_Send(hClntSock, "ID 길이가 5를 넘습니다.");
				_sender->SendEnter(hClntSock);
				return;
			}

			_userState.setID(LOGIN_ID);

			_sender->_SendLogined(hClntSock);
			_userState.SetLoginState(true);

			std::cout << "[ " << _userState.GetID() << " ] " << str;
		}

	}

	if (_userState.GetID() == "")  //유저정보가 등록되어 있지 않다면 바로 리턴.
	{
		_sender->_SendLogin(hClntSock);
		_sender->SendEnter(hClntSock);
		return;
	}

	if (commands != COMMANDS::LOGIN && _userState.GetLoginState() == true)	//명령어가 LOGIN이 아니고 로그인한 상태라면 다른 명령어를 분기처리한다.
	{
		switch (commands)
		{
		case COMMANDS::CL: //CommandsList
			_sender->_SendCL(hClntSock);
			break;

		case COMMANDS::MR: //MakeRoom
		{
			if (_userState.GetIsEnteredRoom() == true) //이미 방에 접속중이라면 명령어 무시
			{
				_sender->_Send(hClntSock, "이미 방에 입장중입니다.");
				_sender->SendEnter(hClntSock);
				return;
			}

			if (COMMANDS_PARAMETERS_VECTOR.size() < MAKE_ROOM_PARAMETERS_COUNTS)
			{
				_sender->_Send(hClntSock, "방의 정보를 입력하세요. /MR [ 방 이름 ] [ 최대 인원 ] [ 비밀번호 (안적으면 공개방 생성) ]");
				_sender->SendEnter(hClntSock);
				break;
			}


			if (COMMANDS_PARAMETERS_VECTOR.size() > MAKE_ROOM_PARAMETERS_COUNTS) //비공개방 생성
			{
				_roomManager->MakeRoom(ROOM_NAME, ROOM_MAX_USER_COUNTS, MAKE_ROOM_PASSWORD);
				if (_roomManager->EnterRoom(_roomManager->nextRoomNum - 1, _userState, MAKE_ROOM_PASSWORD) == true) //방금 만든 방에 접속하기 위해 -1로 보정후 접속.
				{
					_sender->_SendRE(hClntSock);
				}
			}
			else if (COMMANDS_PARAMETERS_VECTOR.size() == MAKE_ROOM_PARAMETERS_COUNTS) //공개방 생성
			{
				_roomManager->MakeRoom(ROOM_NAME, ROOM_MAX_USER_COUNTS);
				if (_roomManager->EnterRoom(_roomManager->nextRoomNum - 1, _userState) == true) //방금 만든 방에 접속하기 위해 -1로 보정후 접속.
				{
					_sender->_SendRE(hClntSock);
				}
			}

			break;
		}

		case COMMANDS::RE: //RoomEnter
		{
			if (_userState.GetIsEnteredRoom() == true) //이미 방에 접속중이라면 명령어 무시
			{
				_sender->_Send(hClntSock, "이미 방에 입장중입니다.");
				_sender->SendEnter(hClntSock);
				return;
			}

			if (COMMANDS_PARAMETERS_VECTOR.size() < NONE_ENTER_ROOM_PARAMETERS) //접속하려는 방의 정보를 입력하지 않으면 break
			{
				_sender->_Send(hClntSock, "접속하시려는 방의 정보를 입력하세요. /RE [ 방 번호 ] [ 비밀번호 ]");
				_sender->SendEnter(hClntSock);
				break;
			}

			string password;
			int roomNum = stoi(_stringDistinguisher.commandsParametersListVec[1]);
			if (COMMANDS_PARAMETERS_VECTOR.size() > NONE_ENTER_ROOM_PARAMETERS) //비밀번호까지 같이 입력했다면 true (공개방 입장인데 비밀번호를 입력했어도 입장가능)
				password = ENTER_ROOM_PASSWORD;

			if (_roomManager->EnterRoom(roomNum, _userState, password) == true) //방 입장 성공
			{
				_sender->_SendRE(hClntSock);
			}

			else
				_sender->_Send(hClntSock, "입장 실패.\r\n");

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
			if (COMMANDS_PARAMETERS_VECTOR.size() < TO_PARAMETERS_COUNTS - 1) //귓속말을 받는 사람의 아이디, 귓속말의 내용까지 모두 명령어로 입력하지 않았으면 break
			{
				_sender->_Send(hClntSock, "받는 사람의 아이디를 입력하세요.\r\n");
				break;
			}

			if (COMMANDS_PARAMETERS_VECTOR.size() < TO_PARAMETERS_COUNTS) //귓속말을 받는 사람의 아이디, 귓속말의 내용까지 모두 명령어로 입력하지 않았으면 break
			{
				_sender->_Send(hClntSock, "내용을 입력하세요.\r\n");
				break;
			}

			SOCKET receiverSock;		   //받는 사람
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
			_sender->_Send(hClntSock, "접속하지 않은 ID 입니다.\r\n");
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
			if (_userState.GetIsEnteredRoom() == false) //로비에서 RoomInfo명령어를 호출하면 무시한다.
			{
				_sender->_Send(hClntSock, "방에 입장해서 사용할 수 있는 명령어 입니다.");
				_sender->SendEnter(hClntSock);

				break;
			}

			_sender->_SendRI(hClntSock);

#define USER_ROOM _roomManager->_roomMap[_userState.GetRoomNum()] //user가 존재하는 room 접근
			string message;
			message += (to_string(USER_ROOM.roomNum) + "\t\t" + USER_ROOM.name + "\t" + to_string(USER_ROOM.userRoomMap.size()) + " / " + to_string(USER_ROOM.maxUserCount));
			_sender->_Send(hClntSock, message.c_str());
			_sender->SendEnter(hClntSock);
			_sender->_SendRUI(hClntSock);

#define MAX_PRINT_USER_ID_COUNT 5 //한 줄에 최대 몇명까지 표시해줄것인지 정한다
			string userID;
			int userCount = 0;
			for (auto iter = USER_ROOM.userRoomMap.begin(); iter != USER_ROOM.userRoomMap.end(); iter++) //해당방에 있는 모든 유저의 아이디를 보기 위한 반복문
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
			_sender->_Send(hClntSock, "올바르지 않은 명령어 입니다. 명령어 보기 : /CL");
			_sender->SendEnter(hClntSock);
			return;   //올바르지 않은 명령어가 들어오면 바로 리턴.
		}

		std::cout << "[ " << _userState.GetID() << " ] " << str << endl;

	}
}

void TcpSession::_CloseClient()
{
	UserState userState;  //유저가 종료할 때 입장중이던 방에서 아웃처리하도록 구현
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


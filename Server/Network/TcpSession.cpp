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

	else if (_receiver->_buf[_receiver->_strLen - 1] == '\b')//입력들어온 데이터의 가장 마지막 문자가 백 스페이스일 때
	{
		_receiver->InputBackSpace();
		_sender->_Send(hClntSock, " ");
		_sender->_Send(hClntSock, "\b");
	}

	else if (_receiver->_buf[_receiver->_strLen - 1] == '\n')  //입력들어온 데이터의 가장 마지막 문자가 개행문자일 때
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
		COMMANDS commands = _stringDistinguisher.WhatCommands(str);
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

	string message = ("[ " + _userState.GetID() + " ]");
	message += (" " + str);

	if (_userState.GetIsEnteredRoom() == false) //로비에서 채팅을 입력했다면
	{
#define SESSION iter->second
		for (auto iter = _userMap->begin(); iter != _userMap->end(); iter++)
		{
			if (SESSION->_userState.GetIsEnteredRoom() == false) //로비에 있는 유저를 탐색
			{
				SOCKET sock = SESSION->hClntSock;
				_sender->_Send(sock, message.c_str());
				_sender->SendEnter(sock); //메시지를 받으면 개행처리한다
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
			return;

		if (COMMANDS_PARAMETERS_VECTOR.size() > NONE_LOGIN_PARAMETERS)
			_userState.setID(LOGIN_ID);

		_sender->_SendLogined(hClntSock);
		_userState.SetLoginState(true);

		std::cout << "[ " << _userState.GetID() << " ] " << str << endl;

	}

	if (_userState.GetID() == "")  //유저정보가 등록되어 있지 않다면 바로 리턴.
		return;

	if (commands != COMMANDS::LOGIN && _userState.GetLoginState() == true)	//명령어가 LOGIN이 아니고 로그인한 상태라면 다른 명령어를 분기처리한다.
	{
		//TODO : 명령어들별로 함수화 시키기
		switch (commands)
		{
		case COMMANDS::CL: //CommandsList
			_sender->_SendCL(hClntSock);
			break;

		case COMMANDS::MR: //MakeRoom
		{
			if (_userState.GetIsEnteredRoom() == true) //이미 방에 접속중이라면 명령어 무시
				return;

			if (COMMANDS_PARAMETERS_VECTOR.size() > MAKE_ROOM_PARAMETERS_COUNTS) //비공개방 생성
			{
				_roomManager->MakeRoom(ROOM_NAME, stoi(_stringDistinguisher.commandsParametersListVec[2]), MAKE_ROOM_PASSWORD);
				if (_roomManager->EnterRoom(_roomManager->nextRoomNum - 1, _userState, MAKE_ROOM_PASSWORD) == true) //방금 만든 방에 접속하기 위해 -1로 보정후 접속. _roomManager->nextRoomNum-1
				{
					_sender->_SendRE(hClntSock);
				}
			}
			else if (COMMANDS_PARAMETERS_VECTOR.size() == MAKE_ROOM_PARAMETERS_COUNTS) //공개방 생성
			{
				_roomManager->MakeRoom(ROOM_NAME, stoi(_stringDistinguisher.commandsParametersListVec[2]));
				if (_roomManager->EnterRoom(_roomManager->nextRoomNum - 1, _userState) == true) //방금 만든 방에 접속하기 위해 -1로 보정후 접속. _roomManager->nextRoomNum-1
				{
					_sender->_SendRE(hClntSock);
				}
			}

			break;
		}

		case COMMANDS::RE: //RoomEnter
		{
			if (_userState.GetIsEnteredRoom() == true) //이미 방에 접속중이라면 명령어 무시
				return;

			if (COMMANDS_PARAMETERS_VECTOR.size() < NONE_ENTER_ROOM_PARAMETERS) //접속하려는 방의 정보를 입력하지 않으면 break
				break;

			string password;
			int roomNum = stoi(_stringDistinguisher.commandsParametersListVec[1]);
			if (COMMANDS_PARAMETERS_VECTOR.size() > NONE_ENTER_ROOM_PARAMETERS) //비밀번호까지 같이 입력했다면 true (공개방 입장인데 비밀번호를 입력했어도 입장가능)
				password = ENTER_ROOM_PASSWORD;

			if (_roomManager->EnterRoom(roomNum, _userState, password) == true) //방 입장 성공
			{
				_sender->_SendRE(hClntSock);
			}

			else
				_sender->_Send(hClntSock, "입장 실패.");

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
			if (COMMANDS_PARAMETERS_VECTOR.size() < TO_PARAMETERS_COUNTS) //귓속말을 받는 사람의 아이디, 귓속말의 내용까지 모두 명령어로 입력하지 않았으면 break
			{
				_sender->_Send(hClntSock, "내용을 입력하세요.\r\n");
				break;
			}

			SOCKET senderSock = hClntSock; //보내는 사람
			SOCKET receiverSock;		   //받는 사람
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

					message = ("[귓속말] " + _userState.GetID() + " : " + message);
					_sender->_Send(receiverSock, message.c_str());
					_sender->_Send(receiverSock, "\r\n");

					return;;
				}
			}
			_sender->_Send(hClntSock, "접속하지 않은 ID 입니다.\r\n");
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
			if (_userState.GetIsEnteredRoom() == false) //로비에서 RoomInfo명령어를 호출하면 무시한다.
				break;

			_sender->_SendRI(hClntSock);

#define ROOM _roomManager->_roomMap[_userState.GetRoomNum()] //user가 존재하는 room 접근
			string message;
			message += (to_string(ROOM.roomNum) + "\t\t" + ROOM.name + "\t" + to_string(ROOM.userRoomMap.size()) + " / " + to_string(ROOM.maxUserCount));
			_sender->_Send(hClntSock, message.c_str());
			_sender->SendEnter(hClntSock);
			_sender->_SendRUI(hClntSock);

#define MAX_PRINT_USER_ID_COUNT 5 //한 줄에 최대 몇명까지 표시해줄것인지 정한다
			string userID;
			int userCount = 0;
			for (auto iter = ROOM.userRoomMap.begin(); iter != ROOM.userRoomMap.end(); iter++) //해당방에 있는 모든 유저의 아이디를 보기 위한 반복문
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
			return;   //올바르지 않은 명령어가 들어오면 바로 리턴.
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


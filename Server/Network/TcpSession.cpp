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

	else		//str이 명령어가 아니라면 (채팅이라면) 해당 클라의 방번호로 채팅 전송. 로비에있다면 로비로 채팅 전송
	{
		_ProcessingChatting(str);
	}
}

void TcpSession::_ProcessingChatting(string str)
{
	if (us.GetLoginState() == false) //로그인하지 않은 상태라면 무시한다
		return;

	string message = ( "[ " + us.GetID() + " ]");
	message += (" " + str);

	if (us.GetIsEnteredRoom() == false) //로비에서 채팅을 입력했다면
	{
#define SESSION iter->second
		for (auto iter = _userMap->begin(); iter != _userMap->end(); iter++)
		{
			if (SESSION->us.GetIsEnteredRoom() == false) //로비에 있는 유저를 탐색
			{
				SOCKET sock = SESSION->hClntSock;
				_sender->_Send(sock, message.c_str());
				_sender->SendEnter(sock); //메시지를 받으면 개행처리한다
			}
		}
	}

	else if (us.GetIsEnteredRoom() == true) //방에서 채팅을 입력했다면
	{
#define USER iter->second
		for (auto iter = _roomManager->_roomMap.begin(); iter != _roomManager->_roomMap.end(); iter++) //해당 방을 찾아서
		{
#define ROOM iter->second
			if (ROOM.roomNum == us.GetRoomNum())
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
	if (commands == COMMANDS::LOGIN && us.GetLoginState() == false)  //명령어가 LOGIN이면서 로그인한 상태가 아니라면
	{
		if (_stringDistinguisher.v.size() <= 1) //LOGIN명령어인데 매개변수 없이 입력한 경우는 리턴.
			return;

		if (_stringDistinguisher.v.size() > 1)
			us.setID(_stringDistinguisher.v[1]);

		_sender->_SendLogined(hClntSock);
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
			_sender->_SendCL(hClntSock);
			break;

		case COMMANDS::MR: //MakeRoom
		{
			if (us.GetIsEnteredRoom() == true) //이미 방에 접속중이라면 명령어 무시
				return;

			string enterStr;
			if (_stringDistinguisher.v.size() > 3) //비공개방 생성
			{
				_roomManager->MakeRoom(_stringDistinguisher.v[1], stoi(_stringDistinguisher.v[2]), stoi(_stringDistinguisher.v[3]));
				_sender->_SendMR(hClntSock);
				if (_roomManager->EnterRoom(_roomManager->nextRoomNum - 1, us, stoi(_stringDistinguisher.v[3])) == true) //방금 만든 방에 접속하기 위해 -1로 보정후 접속. _roomManager->nextRoomNum-1
				{
					_sender->_SendRE(hClntSock);
				}
			}
			else if (_stringDistinguisher.v.size() == 3) //공개방 생성
			{
				_roomManager->MakeRoom(_stringDistinguisher.v[1], stoi(_stringDistinguisher.v[2]));
				_sender->_SendMR(hClntSock);
				if (_roomManager->EnterRoom(_roomManager->nextRoomNum - 1, us) == true) //방금 만든 방에 접속하기 위해 -1로 보정후 접속. _roomManager->nextRoomNum-1
				{
					_sender->_SendRE(hClntSock);
				}
			}

			_ProcessingCommands(COMMANDS::RE, enterStr);

			break;
		}

		case COMMANDS::RE: //RoomEnter
		{
			if (us.GetIsEnteredRoom() == true) //이미 방에 접속중이라면 명령어 무시
				return;

			if (_stringDistinguisher.v.size() < 2) //접속하려는 방의 정보를 입력하지 않으면 break
				break;

			int password = 0;
			int roomNum = stoi(_stringDistinguisher.v[1]); //TODO : string, int 구별하기
			if (_stringDistinguisher.v.size() > 2) //비밀번호까지 같이 입력했다면 true (공개방 입장인데 비밀번호를 입력했어도 입장가능)
				password = stoi(_stringDistinguisher.v[2]);

			if (_roomManager->EnterRoom(roomNum, us, password) == true) //방 입장 성공
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
			if (_stringDistinguisher.v.size() < 3) //귓속말을 받는 사람의 아이디, 귓속말의 내용까지 모두 명령어로 입력하지 않았으면 break
			{
				_sender->_Send(hClntSock, "내용을 입력하세요.\r\n");
				break;
			}

			SOCKET senderSock = hClntSock; //보내는 사람
			SOCKET receiverSock;		   //받는 사람
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

					message = ("[귓속말] " + us.GetID() + " : " + message);
					_sender->_Send(receiverSock, message.c_str());
					_sender->_Send(receiverSock, "\r\n");

					return;;
				}
			}
			_sender->_Send(hClntSock, "접속하지 않은 ID 입니다.\r\n");
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


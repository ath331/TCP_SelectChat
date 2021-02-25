#pragma once
#include "TcpSession.h"

#include <vector>

#define ROOM_NUM int
#define USER_NUM SOCKET

class RoomManager
{
public:
	RoomManager();
	~RoomManager();

	void MakeRoom(string name, string maxUserCount, string password = "@!2209ASd");	//방 생성 성공시 true 리턴
	bool EnterRoom(int roomNum, UserState& user, string password = "@!2209ASd");		//방 참여 성공시 true 리턴
	void OutRoom(int roomNum, UserState& user);							//방 나가기 성공시 true 리턴

private:
	struct Room
	{
		Room() {}
		Room(string name, int maxUserCount, string password = "@!2209ASd")
			:name(name), maxUserCount(maxUserCount), password(password)
		{
			if (password != "@!2209ASd")
				isPrivateRoom = true;
		}

		string name;

		int roomNum = -1;
		int maxUserCount = 0;

		bool isPrivateRoom = false;
		string password = "-1";
		unordered_map<USER_NUM, UserState> userRoomMap; //room안에 있는 유저들
	};

	int nextRoomNum = 1; //방이 생성될 때 배정하는 번호
	unordered_map<ROOM_NUM, Room> _roomMap;

private:
	void DeleteRoom(int roomNum);

public:
	friend TcpSession;
};


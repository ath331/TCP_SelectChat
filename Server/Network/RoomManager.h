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

	void MakeRoom(string name, int maxUserCount, string password = "-1");	//방 생성 성공시 true 리턴
	bool EnterRoom(int roomNum, UserState& user, string password = "-1");		//방 참여 성공시 true 리턴
	void OutRoom(int roomNum, UserState& user);							//방 나가기 성공시 true 리턴

private:
	struct Room
	{
		Room() {}
		Room(string name, int maxUserCount, string password = "-1")
			:name(name), maxUserCount(maxUserCount), password(password)
		{
			if (password != "-1")
				isPrivateRoom = true;
		}

		string name;

		int roomNum = -1;
		int maxUserCount = 0;

		bool isPrivateRoom = false;
		string password = "-1";
		map<USER_NUM, UserState> userRoomMap; //room안에 있는 유저들
	};

	int nextRoomNum = 1; //방이 생성될 때 배정하는 번호
	map<ROOM_NUM, Room> _roomMap;

private:
	void DeleteRoom(int roomNum);

public:
	friend TcpSession;
};


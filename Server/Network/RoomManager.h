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

	void MakeRoom(string name, int maxUserCount, string password = "-1");	//�� ���� ������ true ����
	bool EnterRoom(int roomNum, UserState& user, string password = "-1");		//�� ���� ������ true ����
	void OutRoom(int roomNum, UserState& user);							//�� ������ ������ true ����

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
		map<USER_NUM, UserState> userRoomMap; //room�ȿ� �ִ� ������
	};

	int nextRoomNum = 1; //���� ������ �� �����ϴ� ��ȣ
	map<ROOM_NUM, Room> _roomMap;

private:
	void DeleteRoom(int roomNum);

public:
	friend TcpSession;
};


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

	void MakeRoom(string name, string maxUserCount, string password = "@!2209ASd");	//�� ���� ������ true ����
	bool EnterRoom(int roomNum, UserState& user, string password = "@!2209ASd");		//�� ���� ������ true ����
	void OutRoom(int roomNum, UserState& user);							//�� ������ ������ true ����

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
		unordered_map<USER_NUM, UserState> userRoomMap; //room�ȿ� �ִ� ������
	};

	int nextRoomNum = 1; //���� ������ �� �����ϴ� ��ȣ
	unordered_map<ROOM_NUM, Room> _roomMap;

private:
	void DeleteRoom(int roomNum);

public:
	friend TcpSession;
};


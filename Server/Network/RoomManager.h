#pragma once
#include "TcpSession.h"

#include <vector>

class TcpSession;
class RoomManager
{
public:
	RoomManager();
	~RoomManager();

	void MakeRoom(string name, int maxUserCount, int password = -1);	//�� ���� ������ true ����
	bool EnterRoom(int roomNum, UserState& user, int password = -1);		//�� ���� ������ true ����
	void OutRoom(int roomNum, UserState& user);							//�� ������ ������ true ����

private:
	struct Room
	{
		Room() {}
		Room(string name, int maxUserCount, int password = -1)
			:name(name), maxUserCount(maxUserCount), password(password)
		{
			if (password != -1)
				isPrivateRoom = true;
		}

		string name;

		int roomNum = -1;
		int maxUserCount = 0;

		bool isPrivateRoom = false;
		int password = -1;
		vector<UserState> userRoomVec; //room�ȿ� �ִ� ������
	};

	int nextRoomNum = 1; //���� ������ �� �����ϴ� ��ȣ
	map<int, Room> _roomMap;

private:
	void DeleteRoom(int roomNum);

public:
	friend TcpSession;
};


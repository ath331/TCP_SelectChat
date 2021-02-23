#include "RoomManager.h"



RoomManager::RoomManager()
{
}


RoomManager::~RoomManager()
{
}

void RoomManager::MakeRoom(string name, int maxUserCount, int password)
{
	Room room(name, maxUserCount, password);
	room.roomNum = nextRoomNum++;

	_roomMap.insert(make_pair(room.roomNum, room));
}

bool RoomManager::EnterRoom(int roomNum, UserState& user, int password)
{
	Room room;
	for (int i = 0; i < _roomMap.size(); i++)
	{
		if (roomNum == _roomMap[i].roomNum) //������ ��ȣ�� ���� �����Ѵٸ�
		{
			room = _roomMap[i];
			if (room.userRoomVec.size() + 1 <= room.maxUserCount) //���� �ο��� �� �� �߰��ص� �ִ��ο��� ���� �ʴ´ٸ�
			{
				if (room.isPrivateRoom == false) //���� �������̶��
				{
					room.userRoomVec.push_back(user);
					user.SetRoomNum(roomNum);
				}
				else //���� ����� ���̶��
				{
					if (room.password != password)
					{
						room.userRoomVec.push_back(user);
						user.SetRoomNum(roomNum);
					}
					else
						return false;
				}
			}

			return false; //���� �ο��� �� �� �߰��ص� �ִ��ο��� �Ѵ´ٸ�
		}
	}

	return false; //������ ��ȣ�� ���� �������� �ʴ´ٸ�
}

void RoomManager::OutRoom(int roomNum, UserState& user)
{
	Room room = _roomMap[roomNum];
	user.SetRoomNum(0); //�κ��� ��ȣ�� 0���� ����

	for (int i = 0; i < room.userRoomVec.size(); i++)
	{
	}
}

void RoomManager::DeleteRoom(int roomNum)
{

}

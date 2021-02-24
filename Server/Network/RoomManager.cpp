#include "RoomManager.h"



RoomManager::RoomManager()
{
}


RoomManager::~RoomManager()
{
}

void RoomManager::MakeRoom(string name, int maxUserCount, string password)
{
	Room room(name, maxUserCount, password);
	room.roomNum = nextRoomNum++;

	_roomMap.insert(make_pair(room.roomNum, room));
}

bool RoomManager::EnterRoom(int roomNum, UserState& user, string password)
{
#define ROOM iter->second

	for (auto iter = _roomMap.begin(); iter != _roomMap.end(); iter++)
	{
		if (roomNum == ROOM.roomNum) //������ ��ȣ�� ���� �����Ѵٸ�
		{
			if (ROOM.userRoomMap.size() + 1 <= ROOM.maxUserCount) //���� �ο��� �� �� �߰��ص� �ִ��ο��� ���� �ʴ´ٸ�
			{
				if (ROOM.isPrivateRoom == false) //���� �������̶��
				{
					ROOM.userRoomMap.insert(make_pair(user.hClntSock, user));
					user.SetRoomNum(roomNum);
					user.SetIsEnteredRoom(true);

					return true;
				}
				else //���� ����� ���̶��
				{
					if (ROOM.password == password) //�Է��� ��й�ȣ�� �´ٸ�
					{
						ROOM.userRoomMap.insert(make_pair(user.hClntSock, user));
						user.SetRoomNum(roomNum);
						user.SetIsEnteredRoom(true);

						return true;
					}
					else
						return false; //���� ����� ���ε� ��й�ȣ�� �ٸ���
				}
			}

			return false; //���� �ο��� �� �� �߰��ص� �ִ��ο��� �Ѵ´ٸ�
		}
	}

	return false; //������ ��ȣ�� ���� �������� �ʴ´ٸ�
}

void RoomManager::OutRoom(int roomNum, UserState& user)
{
#define ROOM iter->second
	for (auto iter = _roomMap.begin(); iter != _roomMap.end(); iter++)
	{
		if (roomNum == ROOM.roomNum)
		{
			user.SetRoomNum(0);
			user.SetIsEnteredRoom(false);

			ROOM.userRoomMap.erase(user.hClntSock);

			if (ROOM.userRoomMap.size() < 1)
			{
				DeleteRoom(roomNum);
				break;
			}
		}
	}
}

void RoomManager::DeleteRoom(int roomNum)
{
	_roomMap.erase(roomNum);
}

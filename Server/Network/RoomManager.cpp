#include "RoomManager.h"

#define ROOM iter->second

RoomManager::RoomManager()
{
}

RoomManager::~RoomManager()
{
}

const int DEFAULT_MAX_ROOM_USER_COUNTS = 10;

void RoomManager::MakeRoom(string name, string maxUserCount, string password)
{
	int roomMaxUserCount = 0;
	try
	{
		roomMaxUserCount = stoi(maxUserCount);
	}
	catch (const std::exception&)
	{
		roomMaxUserCount = DEFAULT_MAX_ROOM_USER_COUNTS; //���ڿ��� ������ maxUserCount�� intŸ������ ��ȯ�� �� ������ �����(�ο��� ���ڷ� �Է��� ��) ����Ʈ ������ ����.
	}

	if (roomMaxUserCount < 1)
		maxUserCount = DEFAULT_MAX_ROOM_USER_COUNTS; //�ο��� �����̸� ����Ʈ ������ ����

	Room room(name, roomMaxUserCount, password);
	room.roomNum = nextRoomNum++;

	_roomMap.insert(make_pair(room.roomNum, room));
}

bool RoomManager::EnterRoom(int roomNum, UserState& user, string password)
{

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

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
		if (roomNum == ROOM.roomNum) //들어가려는 번호의 방이 존재한다면
		{
			if (ROOM.userRoomMap.size() + 1 <= ROOM.maxUserCount) //방의 인원을 한 명 추가해도 최대인원을 넘지 않는다면
			{
				if (ROOM.isPrivateRoom == false) //방이 공개방이라면
				{
					ROOM.userRoomMap.insert(make_pair(user.hClntSock, user));
					user.SetRoomNum(roomNum);
					user.SetIsEnteredRoom(true);

					return true;
				}
				else //방이 비공개 방이라면
				{
					if (ROOM.password == password) //입력한 비밀번호가 맞다면
					{
						ROOM.userRoomMap.insert(make_pair(user.hClntSock, user));
						user.SetRoomNum(roomNum);
						user.SetIsEnteredRoom(true);

						return true;
					}
					else
						return false; //방이 비공개 방인데 비밀번호가 다르면
				}
			}

			return false; //방의 인원을 한 명 추가해도 최대인원을 넘는다면
		}
	}

	return false; //들어가려는 번호의 방이 존재하지 않는다면
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

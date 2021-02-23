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
		if (roomNum == _roomMap[i].roomNum) //들어가려는 번호의 방이 존재한다면
		{
			room = _roomMap[i];
			if (room.userRoomVec.size() + 1 <= room.maxUserCount) //방의 인원을 한 명 추가해도 최대인원을 넘지 않는다면
			{
				if (room.isPrivateRoom == false) //방이 공개방이라면
				{
					room.userRoomVec.push_back(user);
					user.SetRoomNum(roomNum);
				}
				else //방이 비공개 방이라면
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

			return false; //방의 인원을 한 명 추가해도 최대인원을 넘는다면
		}
	}

	return false; //들어가려는 번호의 방이 존재하지 않는다면
}

void RoomManager::OutRoom(int roomNum, UserState& user)
{
	Room room = _roomMap[roomNum];
	user.SetRoomNum(0); //로비의 번호인 0으로 세팅

	for (int i = 0; i < room.userRoomVec.size(); i++)
	{
	}
}

void RoomManager::DeleteRoom(int roomNum)
{

}

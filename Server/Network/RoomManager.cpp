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
		roomMaxUserCount = DEFAULT_MAX_ROOM_USER_COUNTS; //문자열로 들어오는 maxUserCount를 int타입으로 변환할 떄 오류가 생기면(인원을 문자로 입력할 때) 디폴트 값으로 보정.
	}

	if (roomMaxUserCount < 1)
		maxUserCount = DEFAULT_MAX_ROOM_USER_COUNTS; //인원이 음수이면 디폴트 값으로 보정

	Room room(name, roomMaxUserCount, password);
	room.roomNum = nextRoomNum++;

	_roomMap.insert(make_pair(room.roomNum, room));
}

bool RoomManager::EnterRoom(int roomNum, UserState& user, string password)
{

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

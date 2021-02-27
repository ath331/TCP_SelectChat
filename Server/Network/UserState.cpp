#include "UserState.h"
#include "TcpSession.h"

UserState::~UserState()
{
}

std::string UserState::GetID()
{
	return _id;
}

void UserState::setID(std::string id)
{
	_id = id;
}

int UserState::GetRoomNum()
{
	return _roomNum;
}

void UserState::SetRoomNum(int roomNum)
{
	_roomNum = roomNum;
}

bool UserState::GetLoginState()
{
	return _isLogined;
}

void UserState::SetLoginState(bool b)
{
	_isLogined = b;
}

bool UserState::GetIsEnteredRoom()
{
	return _isEnteredRoom;
}

void UserState::SetIsEnteredRoom(bool b)
{
	_isEnteredRoom = b;
}
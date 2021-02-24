#pragma once
#include <string>
#include <WinSock2.h>

class UserState
{
public:
	UserState()
	{}
	UserState(SOCKET sock)
		:hClntSock(sock)
	{

	}
	~UserState();

	SOCKET hClntSock;

	std::string GetID();
	void setID(std::string id);

	int GetRoomNum();
	void SetRoomNum(int roomNum);

	bool GetLoginState();
	void SetLoginState(bool b);

	bool GetIsEnteredRoom();
	void SetIsEnteredRoom(bool b);

private:
	std::string _id;

	int _roomNum		= 0;
	bool _isLogined		= false;
	bool _isEnteredRoom = false;
};


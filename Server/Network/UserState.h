#pragma once
#include <string>

class TcpSession;
class UserState
{
public:
	UserState()
	{}
	UserState(TcpSession* session)
		:tcpSession(session)
	{

	}
	~UserState();

	TcpSession* tcpSession;

	std::string GetID();
	void setID(std::string id);

	int GetRoomNum();
	void SetRoomNum(int roomNum);

	bool GetLoginState();
	void SetLoginState(bool b);

private:
	std::string _id;
	int _roomNum		= 0;
	bool _isLogined		= false;
};


#pragma once
#include "StringDistinguisher.h"
#include "UserState.h"

#include <WinSock2.h>
#include <map>

using namespace std;

class RoomManager;
class Accepter;
class Receiver;
class Sender;
class TcpSession
{
public:
	TcpSession(RoomManager* roomManager, map<SOCKET, TcpSession*>* userMap, SOCKET sock, fd_set* reads);
	~TcpSession();

	void RecvClient();

	SOCKET hClntSock = 0;
private:
	UserState us;

	map<SOCKET, TcpSession*>* _userMap;
	RoomManager* _roomManager;
	fd_set* _reads;

	Accepter* _accept;
	Receiver* _receiver;
	Sender* _sender;

	StringDistinguisher _stringDistinguisher;

private:
	void _Accept();
	void _CloseClient();

	void _IsCommands(string str);
	void _ProcessingCommands(COMMANDS commands, string str);
	void _ProcessingChatting(string str);
};


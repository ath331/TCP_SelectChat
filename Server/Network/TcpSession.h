#pragma once
#include "StringDistinguisher.h"
#include "UserState.h"

#include <WinSock2.h>
#include <map>

using namespace std;

class Accepter;
class Receiver;
class Sender;
class TcpSession
{
public:
	TcpSession(map<SOCKET, UserState>* userMap, SOCKET sock, fd_set* reads);
	~TcpSession();

	void RecvClient();

	SOCKET hClntSock = 0;
private:
	map<SOCKET, UserState>* _userMap;
	fd_set* _reads;

	Accepter* _accept;
	Receiver* _receiver;
	Sender* _sender;

	StringDistinguisher _stringDistinguisher;

private:
	void _Accept();
	void _CloseClient();

	void _IsCommands(string str);
	void _ProcessingCommands(COMMANDS commands);
};


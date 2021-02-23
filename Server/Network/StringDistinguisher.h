//문자열이 명령어인지 채팅인지 판별하는 클래스
//명령어라면 무슨 명령어인지 리턴한다.

#pragma once
#include <string>
#include <vector>

using namespace std;

enum class COMMANDS : int
{
	LOGIN,					 
	CL,						 //CommandsList. 명령어 목록
	UL,						 //유저리스트
	MR,						 //Make Room
	RL,						 //Room List
	RE,						 //Room Enter
	TO,						 //귓속말
	ENUM_COMMANDS_MAX_COUNT, //COMMANDS의 ENUM값이 몇 개인지 쉽게 알기위한 값
};

class StringDistinguisher
{
public:
	StringDistinguisher();
	~StringDistinguisher();

	bool IsCommands(string str);				//str이 명령어라면 true 리턴
	COMMANDS WhatCommands(string commands);		//commands를 enum 값을 리턴

	vector<string> v;							//명령어 뒤의 오는 단어들을 저장하는 벡터. 인덱스 0에는 명령어가 저장된다.
private:
	void _splitStr(string str);
};


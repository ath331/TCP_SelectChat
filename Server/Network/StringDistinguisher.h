//문자열이 명령어인지 채팅인지 판별하는 클래스
//명령어라면 무슨 명령어인지 리턴한다.

#pragma once
#include <string>

using namespace std;

enum class COMMANDS : int
{
	LOGIN,
	ENUM_COMMANDS_MAX_COUNT,					//COMMANDS의 ENUM값이 몇 개인지 쉽게 알기위한 값
};

class StringDistinguisher
{
public:
	StringDistinguisher();
	~StringDistinguisher();

	bool IsCommands(string str);				//str이 명령어라면 true 리턴

	COMMANDS WhatCommands(string commands);		//commands를 enum 값을 리턴
};


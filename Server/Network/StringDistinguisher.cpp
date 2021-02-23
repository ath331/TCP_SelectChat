#include "StringDistinguisher.h"


StringDistinguisher::StringDistinguisher()
{
}


StringDistinguisher::~StringDistinguisher()
{
}

bool StringDistinguisher::IsCommands(string str)
{
	if (str.length() < 1)
		return false;

	if (str[0] != '/')
		return false;

	else
		return true;
}

COMMANDS StringDistinguisher::WhatCommands(string commands)
{
	int index = commands.find(" ");
	string str = commands.substr(1, index - 1);		// 명렁어는 / 부터 시작하므 / 다음 인덱스 부터 추출하기 위해 1을 인자로 넘김

	if (strcmp(str.c_str(), "LOGIN") == 0)
		return COMMANDS::LOGIN;
	if (strcmp(str.c_str(), "CL") == 0)
		return COMMANDS::CL;
	else
		return COMMANDS::ENUM_COMMANDS_MAX_COUNT;
}

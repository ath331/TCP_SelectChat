#include "StringDistinguisher.h"
#include <algorithm>

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
	{
		_splitStr(str);
		return true;
	}
}

void StringDistinguisher::_splitStr(string str)
{
	v.clear();

	int enterCount = count(str.begin(), str.end(), ' ');

	for (int i = 0; i < enterCount + 1; i++)
	{
		string temp;
		int enterCharIndex = str.find(" ");
		temp = str.substr(0, enterCharIndex);
		v.push_back(temp);

		str = str.substr(enterCharIndex + 1, str.length());

	}
}


COMMANDS StringDistinguisher::WhatCommands(string commands)
{
	int index = commands.find(" ");
	string str = commands.substr(1, index - 1);		// 명렁어는 '/' 부터 시작하므로 '/' 다음 인덱스 부터 추출하기 위해 1을 인자로 넘김

	if (strcmp(str.c_str(), "LOGIN") == 0)
		return COMMANDS::LOGIN;
	if (strcmp(str.c_str(), "CL") == 0)
		return COMMANDS::CL;
	if (strcmp(str.c_str(), "MR") == 0)
		return COMMANDS::MR;
	if (strcmp(str.c_str(), "RE") == 0)
		return COMMANDS::RE;
	if (strcmp(str.c_str(), "RL") == 0)
		return COMMANDS::RL;
	if (strcmp(str.c_str(), "TO") == 0)
		return COMMANDS::TO;
	if (strcmp(str.c_str(), "UL") == 0)
		return COMMANDS::UL;
	else
		return COMMANDS::ENUM_COMMANDS_MAX_COUNT;
}

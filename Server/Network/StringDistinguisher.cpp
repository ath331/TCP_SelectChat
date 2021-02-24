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
	string str = commands.substr(1, index - 1); // 명렁어는 / 부터 시작하므 / 다음 인덱스 부터 추출하기 위해 1을 인자로 넘김

	if (COMMANDS_LOGIN == str)
		return COMMANDS::LOGIN;
	if (COMMANDS_CL == str)
		return COMMANDS::CL;
	if (COMMANDS_MR == str)
		return COMMANDS::MR;
	if (COMMANDS_RE == str)
		return COMMANDS::RE;
	if (COMMANDS_RL == str)
		return COMMANDS::RL;
	if (COMMANDS_TO == str)
		return COMMANDS::TO;
	if (COMMANDS_UL == str)
		return COMMANDS::UL;
	if (COMMANDS_Q == str)
		return COMMANDS::Q;
	if (COMMANDS_QUIT == str)
		return COMMANDS::QUIT;
	if (COMMANDS_RI == str)
		return COMMANDS::RI;
	else
		return COMMANDS::ENUM_COMMANDS_MAX_COUNT;
}

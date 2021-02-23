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
	string str = commands.substr(1, index - 1);		// ����� '/' ���� �����ϹǷ� '/' ���� �ε��� ���� �����ϱ� ���� 1�� ���ڷ� �ѱ�

	if (strcmp(str.c_str(), "LOGIN") == 0)
		return COMMANDS::LOGIN;
	if (strcmp(str.c_str(), "CL") == 0)
		return COMMANDS::CL;
	else
		return COMMANDS::ENUM_COMMANDS_MAX_COUNT;
}

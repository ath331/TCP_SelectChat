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
	string str = commands.substr(1, index - 1);		// ����� / ���� �����Ϲ� / ���� �ε��� ���� �����ϱ� ���� 1�� ���ڷ� �ѱ�

	if (strcmp(str.c_str(), "LOGIN") == 0)
		return COMMANDS::LOGIN;
	if (strcmp(str.c_str(), "CL") == 0)
		return COMMANDS::CL;
	else
		return COMMANDS::ENUM_COMMANDS_MAX_COUNT;
}

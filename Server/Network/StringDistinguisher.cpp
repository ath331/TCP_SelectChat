#include "StringDistinguisher.h"
#include <algorithm>

StringDistinguisher::StringDistinguisher()
{
}


StringDistinguisher::~StringDistinguisher()
{
}

bool StringDistinguisher::_IsFirstCharSlash(string str)
{
	if (str == "")
		return false;

	for (int i = 0; i < str.length() - 1; i++)
	{
		if (str[i] != ' ')  //���� ���� ��Ÿ���� ���ڰ� �����̾ƴϸ鼭
		{
			if (str[i] == '/') //'/'�� �����Ѵٸ� ��ɾ��̴�.
				return true;
			else
				return false;
		}
	}
}


bool StringDistinguisher::IsCommands(string& str)
{
	if (str == "")  //�ƹ� ���뵵 ���� ���´ٸ�
		return false;

	_TrimSpace(str);

	if (_IsFirstCharSlash(str) == false)	  // '/'�� �������� �ʴ´ٸ�
		return false;

	else
	{
		_splitStr(str);  //��ɾ��� ��ɾ�� �Բ� �Է¹��� �Ű��������� commandsParametersListVec�� �����Ѵ�
		return true;
	}
}

void StringDistinguisher::_TrimSpace(string& str)
{
	if (str == "")
		return;

	if (str.find(' ') == string::npos)  //���鹮�ڰ� ���� ���ڿ��̶�� ����
		return;

	for (int i = 0; i < str.length() - 1;) //������ �ƴ� ���ڰ� ���� �� ������ ������ ���� "    aa  bb" -> "aa  bb"
	{
		if (str[i] == ' ' || str[i] == '\b')
			str.erase(i, 1);

		else
			break;
	}

	int spaceCharIndex = str.find(' ');  //������ ���ٸ� �ݺ����� ���� �ʴ´�
	for (int i = spaceCharIndex; i < str.length();)
	{
		int nextSpaceCharIndex = str.find(' ', spaceCharIndex + 1);
		if (nextSpaceCharIndex - spaceCharIndex == 1)
			str.erase(spaceCharIndex,1);
		else
		{
			spaceCharIndex = str.find(' ', spaceCharIndex+1);
			if (spaceCharIndex == string::npos)
				break;
		}

	}

}

void StringDistinguisher::_splitStr(string str)
{
	commandsParametersListVec.clear();

	int enterCount = count(str.begin(), str.end(), ' '); //��ĭ�� �������� ����� ��ɾ���� �Ű������� �����Ͽ� �����Ѵ�

	for (int i = 0; i < enterCount + 1; i++)
	{
		string temp;
		int enterCharIndex = str.find(" ");
		temp = str.substr(0, enterCharIndex);
		commandsParametersListVec.push_back(temp);

		str = str.substr(enterCharIndex + 1, str.length());

	}
}


COMMANDS StringDistinguisher::WhatCommands(string commands)
{
	int index = commands.find(" ");
	string str = commands.substr(1, index - 1); // ����� / ���� �����Ϲ� / ���� �ε��� ���� �����ϱ� ���� 1�� ���ڷ� �ѱ�

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

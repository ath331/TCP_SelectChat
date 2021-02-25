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
		if (str[i] != ' ')  //가장 먼저 나타나는 문자가 공백이아니면서
		{
			if (str[i] == '/') //'/'로 시작한다면 명령어이다.
				return true;
			else
				return false;
		}
	}
}


bool StringDistinguisher::IsCommands(string& str)
{
	if (str == "")  //아무 내용도 없이 들어온다면
		return false;

	_TrimSpace(str);

	if (_IsFirstCharSlash(str) == false)	  // '/'로 시작하지 않는다면
		return false;

	else
	{
		_splitStr(str);  //명령어라면 명령어와 함께 입력받은 매개변수들을 commandsParametersListVec에 저장한다
		return true;
	}
}

void StringDistinguisher::_TrimSpace(string& str)
{
	if (str == "")
		return;

	if (str.find(' ') == string::npos)  //공백문자가 없는 문자열이라면 리턴
		return;

	for (int i = 0; i < str.length() - 1;) //공백이 아닌 문자가 나올 때 까지의 공백을 제거 "    aa  bb" -> "aa  bb"
	{
		if (str[i] == ' ' || str[i] == '\b')
			str.erase(i, 1);

		else
			break;
	}

	int spaceCharIndex = str.find(' ');  //공백이 없다면 반복문에 들어가지 않는다
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

	int enterCount = count(str.begin(), str.end(), ' '); //빈칸을 기준으로 명렁어와 명령어들의 매개변수를 구별하여 추출한다

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

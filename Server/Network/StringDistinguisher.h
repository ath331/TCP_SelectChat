//���ڿ��� ��ɾ����� ä������ �Ǻ��ϴ� Ŭ����
//��ɾ��� ���� ��ɾ����� �����Ѵ�.

#pragma once
#include <string>

using namespace std;

enum class COMMANDS : int
{
	LOGIN,
	ENUM_COMMANDS_MAX_COUNT,					//COMMANDS�� ENUM���� �� ������ ���� �˱����� ��
};

class StringDistinguisher
{
public:
	StringDistinguisher();
	~StringDistinguisher();

	bool IsCommands(string str);				//str�� ��ɾ��� true ����

	COMMANDS WhatCommands(string commands);		//commands�� enum ���� ����
};


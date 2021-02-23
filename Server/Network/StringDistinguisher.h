//���ڿ��� ��ɾ����� ä������ �Ǻ��ϴ� Ŭ����
//��ɾ��� ���� ��ɾ����� �����Ѵ�.

#pragma once
#include <string>
#include <vector>

using namespace std;

enum class COMMANDS : int
{
	LOGIN,					 
	CL,						 //CommandsList. ��ɾ� ���
	UL,						 //��������Ʈ
	MR,						 //Make Room
	RL,						 //Room List
	RE,						 //Room Enter
	TO,						 //�ӼӸ�
	ENUM_COMMANDS_MAX_COUNT, //COMMANDS�� ENUM���� �� ������ ���� �˱����� ��
};

class StringDistinguisher
{
public:
	StringDistinguisher();
	~StringDistinguisher();

	bool IsCommands(string str);				//str�� ��ɾ��� true ����
	COMMANDS WhatCommands(string commands);		//commands�� enum ���� ����

	vector<string> v;							//��ɾ� ���� ���� �ܾ���� �����ϴ� ����. �ε��� 0���� ��ɾ ����ȴ�.
private:
	void _splitStr(string str);
};


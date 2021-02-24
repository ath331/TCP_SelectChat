//���ڿ��� ��ɾ����� ä������ �Ǻ��ϴ� Ŭ����
//��ɾ��� ���� ��ɾ����� �����Ѵ�.

#pragma once
#include <string>
#include <vector>

using namespace std;

const string COMMANDS_LOGIN		= "LOGIN";
const string COMMANDS_CL		= "CL";
const string COMMANDS_UL		= "UL";
const string COMMANDS_MR		= "MR";
const string COMMANDS_RL		= "RL";
const string COMMANDS_RE		= "RE";
const string COMMANDS_TO		= "TO";
const string COMMANDS_QUIT		= "QUIT";
const string COMMANDS_Q			= "Q";
const string COMMANDS_RI		= "RI";

enum class COMMANDS : int
{
	LOGIN,
	CL,						 //CommandsList. ��ɾ� ���
	UL,						 //��������Ʈ
	MR,						 //Make Room
	RL,						 //Room List
	RE,						 //Room Enter
	TO,						 //�ӼӸ�
	QUIT,					 //���α׷� ����
	Q,						 //�� ������
	RI,						 //�� ���� ��ȸ
	ENUM_COMMANDS_MAX_COUNT,
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


#pragma once
#include <string>

using namespace std;

class StringSpliter
{
public:
	StringSpliter();
	~StringSpliter();

	string split(string& str);		//str���� \n�� ������ string�� ��ȯ�ϰ� str�� \n���ķ� ������Ʈ
};


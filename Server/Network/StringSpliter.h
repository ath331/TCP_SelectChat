#pragma once
#include <string>

using namespace std;

class StringSpliter
{
public:
	StringSpliter();
	~StringSpliter();

	string split(string& str);		//str���� \n�� ������ string�� �����ϴ� �Լ�.
};


#pragma once
#include <string>

using namespace std;

class StringSpliter
{
public:
	StringSpliter();
	~StringSpliter();

	string split(string& str);		//str에서 \n전 까지의 string을 추출하는 함수.
};


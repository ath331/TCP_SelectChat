//문자열이 명령어인지 채팅인지 판별하는 클래스
//명령어라면 무슨 명령어인지 리턴하고 commandsParametersListVec에 해당 명령어와 같이 들어온 매개변수들을 저장한다.

#pragma once

#include "ParametersDefine.h"

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
	CL,						 //CommandsList. 명령어 목록
	UL,						 //유저리스트
	MR,						 //Make Room
	RL,						 //Room List
	RE,						 //Room Enter
	TO,						 //귓속말
	QUIT,					 //프로그램 종료
	Q,						 //방 나가기
	RI,						 //방 정보 조회
	ENUM_COMMANDS_MAX_COUNT,
};

class StringDistinguisher
{
public:
	StringDistinguisher();
	~StringDistinguisher();

	bool IsCommands(string& str);				//str이 명령어라면 true 리턴
	COMMANDS WhatCommands(string commands);		//commands를 enum 값을 리턴

	vector<string> commandsParametersListVec;	//명령어 뒤의 오는 단어들을 저장하는 벡터. 인덱스 0에는 명령어가 저장된다.
private:
	void _TrimSpace(string& str);				//붙어서온 " "문자를 하나의 " "으로 압축하는 함수.
	void _splitStr(string str);					//str을 공백기준으로 명령어, 명령어와 함께 들어온 매개변수들을 분리하여 commandsParametersListVec에 푸시한다.
	bool _IsFirstCharSlash(string str);			//str에서 가장 먼저 나타나는 공백이 아닌문자가 '/' 인지 판단하는 함수
};


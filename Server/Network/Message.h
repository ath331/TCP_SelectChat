#pragma once
//서버에서 클라로 보내는 여러 메시지들을 모아놓은 헤더

const char* ENTER = "\r\n";

const char* LINE = "====================";

const char* LOGIN = "Please Login. ( /LOGIN [ID] ) ";

const char* LOGINED = "명령어 보기 : /CL\r\n종료 : /QUIT";

const char* CL = "방 생성 : /MR [방 이름] [비밀번호 (안적으면 공개방 생성)]\r\n방 조회 : /RL\r\n방 입장 : /RE [방 번호] [비밀번호]\r\n귓속말  : /TO [ID] [내용]";
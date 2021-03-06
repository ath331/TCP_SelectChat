#pragma once
//서버에서 클라로 보내는 여러 메시지들을 모아놓은 헤더

const char* ENTER = "\r\n";

const char* LINE = "====================";

const char* LOGIN = "Please Login. ( /LOGIN [ ID ] )  ID 최대길이는 5입니다. 명령어는 대/소문자를 구별하지 않습니다.";

const char* LOGINED = "로비에 입장했습니다.\r\n명령어 보기 : /CL\r\n종료 : /QUIT";

const char* CL = "명령어는 대/소문자를 구별하지 않습니다.\r\n유저조회: /UL\r\n방 생성 : /MR [ 방 이름 ] [ 최대 인원 (음수나 문자입력시 10으로 적용)] [ 비밀번호 (안적으면 공개방 생성) ]\r\n방 조회 : /RL\r\n방 입장 : /RE [ 방 번호 ] [ 비밀번호 ]\r\n귓속말  : /TO [ ID ] [ 내용 ]";

const char* RL = "Num  Name  Person(cur/max)  Private(True/False)";

const char* RE = "방에 입장했습니다.\r\n명령어 보기 : /CL\r\n방 나가기   : /Q";

const char* RCL = "유저조회    : /UL\r\n방정보조회  : /RI\r\n귓속말      : /TO [ ID ] [ 내용 ]";

const char* UL = "ID\t방 번호(로비 = 0)";

const char* RI = "RoomNum    RoomName    Person(cur/max)";

const char* RUI = "UserID";
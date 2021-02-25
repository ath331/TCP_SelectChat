#pragma once
//_stringDistinguisher는 명령어가 입력되었을 때 명령어와 명령어의 매개변수들을 분리하는 객체.
//ex) /MR roomName 10 이라는 명령어가 들어오면 
//COMMANDS_PARAMETERS_VECTOR[0] = /MR, 
//COMMANDS_PARAMETERS_VECTOR[1] = roomName, 
//COMMANDS_PARAMETERS_VECTOR[2] = 10 이 저장된다.

#define COMMANDS_PARAMETERS_VECTOR _stringDistinguisher.commandsParametersListVec

#define LOGIN_ID _stringDistinguisher.commandsParametersListVec[1]
#define ROOM_NAME _stringDistinguisher.commandsParametersListVec[1]
#define RECEIVER_ID _stringDistinguisher.commandsParametersListVec[1]
#define MAKE_ROOM_PASSWORD _stringDistinguisher.commandsParametersListVec[3]
#define ENTER_ROOM_PASSWORD _stringDistinguisher.commandsParametersListVec[2]
#define ROOM_MAX_USER_COUNTS = _stringDistinguisher.commandsParametersListVec[2]



const int NONE_LOGIN_PARAMETERS = 1;

const int NONE_ENTER_ROOM_PARAMETERS = 2;

const int MAKE_ROOM_PARAMETERS_COUNTS = 3;

const int TO_PARAMETERS_COUNTS = 3;

const int MESSAGE_INDEX = 2;
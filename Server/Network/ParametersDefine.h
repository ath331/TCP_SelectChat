#pragma once
//_stringDistinguisher�� ��ɾ �ԷµǾ��� �� ��ɾ�� ��ɾ��� �Ű��������� �и��ϴ� ��ü.
//ex) /MR roomName 10 �̶�� ��ɾ ������ 
//COMMANDS_PARAMETERS_VECTOR[0] = /MR, 
//COMMANDS_PARAMETERS_VECTOR[1] = roomName, 
//COMMANDS_PARAMETERS_VECTOR[2] = 10 �� ����ȴ�.

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
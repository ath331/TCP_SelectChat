/*
select에서 TimeOut을 지정하기위한 구조체
*/

#pragma once
#include <WinSock2.h>

struct Timeval
{
	Timeval(long sec, long usec)
	{
		timeval.tv_sec = sec;
		timeval.tv_usec = usec;
	}

	TIMEVAL timeval;

	TIMEVAL* GetPtr()
	{
		return &timeval;
	}
};
/*
select���� TimeOut�� �����ϱ����� ����ü
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
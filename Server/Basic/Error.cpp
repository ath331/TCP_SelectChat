#include <stdio.h>
#include <stdlib.h>

#include "Error.h"
#include "Ptr.h"

void ErrorHandling(char* message)
{
	if (IsCheckNullPtr(message))
	{
		exit(1);
	}

	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
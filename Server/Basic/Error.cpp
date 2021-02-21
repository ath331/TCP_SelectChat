#include <stdio.h>
#include <stdlib.h>

#include "Error.h"

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

void CheckNullPtr(void* ptr)
{
	if (ptr == nullptr)
		ErrorHandling("Ptr is nullptr");
}
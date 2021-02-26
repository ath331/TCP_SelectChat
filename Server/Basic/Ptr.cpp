#include "Ptr.h"

bool IsCheckNullPtr(const void* ptr)
{
	if (ptr == nullptr)
		return true;
	else
		return false;
}
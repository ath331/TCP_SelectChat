#include "Server.h"

int main(int argc, char* argv[])
{
	Server s(argv[1]);
	s.Run();

	return 0;
}
#include "Server.h"

int main(int argc, char* argv[])
{
	Server s(argc > 2 ? argv[1] : "9999");
	s.Run();

	return 0;
}
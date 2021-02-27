<<<<<<< HEAD
#include "Server.h"

int main(int argc, char* argv[])
{
	Server s(argc > 2 ? argv[1] : "9999");
	s.Run();

=======
#include <iostream>

using namespace std;

int main()
{
	cout << "ServerMain" << endl;
>>>>>>> parent of 4de941a (Client브랜치에서 서버 프로젝트 삭제)
	return 0;
}
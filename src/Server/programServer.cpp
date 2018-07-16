#include <iostream>
#include <vector>
#include "Server.hpp"

main () {
    system("cls");
	Server s(std::string("ProgramPipe"));
	s.startServer();
}

//------------------------------------------------------------------------------------------------------------------
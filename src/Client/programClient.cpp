#include <iostream>
#include <climits>
#include "../Client/client.hpp"
#include <time.h>
#include "../Data/Data.hpp"

//------------------------------------------------------------------------------------------------------------------
unsigned int Menu(){
	std::cout << "====== CLIENT MENU ======" << std::endl;

	std::cout << "1 - Insert data" << std::endl;
	std::cout << "2 - Read all data from the server" << std::endl;
	std::cout << "0 - Close client" << std::endl;

	std::cout << "Choose your option: ";
	int answer = 0;
	std::cin >> answer;
	return answer;
}

//==================================================================================================================

main () {
	system ("cls");
	Client client("ProgramPipe");
	unsigned int option  = 0;
	do {
		option = Menu();
		switch (option) {
			case 1: {
                client.requestServerAction(1);
				Data data = client.readData();
				client.writePipeData(data.toString());
				break;
            }
            case 2: {
                client.requestServerAction(2);
                client.readAllServerData();
                break;
            }
		}
	} while (option);
}
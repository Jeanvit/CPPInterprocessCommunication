#include <iostream>
#include <climits>
#include "client.hpp"
#include <time.h>
#include "../Data/Data.hpp"
//------------------------------------------------------------------------------------------------------------------
Client::Client(const std::string& clientName): pipeName(clientName), authKey(authKeyGenerator()){
	std::cout <<"Client initialized with ID number: " << Client::getAuthKey() << std::endl 
		<< "Pipe name: " << Client::getPipeName() << std::endl;
	Client::setPipe();
	Client::openConnection();
	Client::authenticate();	
}

//------------------------------------------------------------------------------------------------------------------
void Client::readAllServerData(){
    std::string serverData;
    std::cout << std::endl << "All server data: " << std::endl;
    do {
        serverData = Client::readPipeData();
        Data data = serverData;
        std::cout << data << std::endl;
    }while (!serverData.empty());

    
}
//------------------------------------------------------------------------------------------------------------------

Data Client::readData(){
	std::string name;
	unsigned int number;
	std::cout << "Enter a name: " << std::endl;
	std::cin>> name;
	Data item(name);
	return item; 
}

//------------------------------------------------------------------------------------------------------------------

std::string Client::readPipeData(){
    char buffer[128];
    DWORD numBytesRead = 0;
    BOOL result = ReadFile(
        Client::getPipe(),
        buffer, 
        127 * sizeof(char), 
        &numBytesRead, 
        NULL 
    );
 
    if (result) {
        buffer[numBytesRead / sizeof(char)] = '\0'; // null terminate the string
        //std::cout << "Bytes read: " << numBytesRead << std::endl;
        //std::cout << "Message: " << buffer << std::endl;
    } else {
        std::cout << "Failed to read data from the pipe." << std::endl;
    }
    return std::string(buffer);
}


//------------------------------------------------------------------------------------------------------------------
bool Client::writePipeData(const std::string& data){
    //std::cout << "Sending data to pipe..." << std::endl;
    BOOL result = ConnectNamedPipe(Client::getPipe(), NULL);
    DWORD numBytesWritten = 0;
    result = WriteFile(
        Client::getPipe(), 
        data.c_str(), 
        sizeof(data) * sizeof(char), 
        &numBytesWritten, 
        NULL 
    );
 
    if (result) {
        //std::cout << "Bytes sent: " << numBytesWritten << std::endl;
        return true;
    } else {
        std::cout << "Failed to send data." << std::endl;
        return false;
    }
}

//------------------------------------------------------------------------------------------------------------------
Client::~Client() {
	CloseHandle(Client::getPipe()); 
    std::cout << "Connection closed" << std::endl; 
    system("pause");

}
//------------------------------------------------------------------------------------------------------------------
void Client::setPipe(){
	 this->currentPipe = CreateFile(
        (pipePrefix + Client::getPipeName()).c_str(),
        PIPE_ACCESS_DUPLEX, 
        PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
}

//------------------------------------------------------------------------------------------------------------------
bool Client::authenticate(){
	Client::writePipeData(std::to_string(Client::getAuthKey()));
	std::string serverResponse = Client::readPipeData();
	if (serverResponse == "1"){
		std::cout << "Your key is valid!" << std::endl;
		return true;
	} else {
		std::cout << "The server rejected this client connection!" << std::endl;
		exit(0);
	}
}


//------------------------------------------------------------------------------------------------------------------
bool Client::openConnection() {
	std::cout << "Connecting to server..." << std::endl; 
    if (Client::getPipe() == INVALID_HANDLE_VALUE) {
        std::cout << "Failed ." << std::endl;
        exit(0);
    }
    return true;
}

//------------------------------------------------------------------------------------------------------------------
unsigned int Client::authKeyGenerator(){
	srand (time(NULL));
	return 2 * ( rand() % INT_MAX );  //Generate only even keys for client validation
}

//------------------------------------------------------------------------------------------------------------------

void Client::requestServerAction(const unsigned int option){
    Client::writePipeData(std::to_string(option));
}

//------------------------------------------------------------------------------------------------------------------
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




	// TEST CODE 
	// This call blocks until a client process connects to the pipe
    /*BOOL result = ConnectNamedPipe(Server::getPipe(), NULL);
    std::cout << "Sending data to pipe..." << std::endl;
    const wchar_t *data = L"*** Hello Pipe World ***";
    DWORD numBytesWritten = 0;
    result = WriteFile(
        Server::getPipe(), // handle to our outbound pipe
        data, // data to send
        wcslen(data) * sizeof(wchar_t), // length of data to send (bytes)
        &numBytesWritten, // will store actual amount of data sent
        NULL // not using overlapped IO
    );
 
    if (result) {
        std::cout << "Number of bytes sent: " << numBytesWritten << std::endl;
    } else {
        std::cout << "Failed to send data." << std::endl;
        // look up error code here using GetLastError()
    }*/



	/*std::cout << "Reading data from pipe..." << std::endl;
 
    // The read operation will block until there is data to read
    wchar_t buffer[128];
    DWORD numBytesRead = 0;
    BOOL result = ReadFile(
        Client::getPipe(),
        buffer, // the data from the pipe will be put here
        127 * sizeof(wchar_t), // number of bytes allocated
        &numBytesRead, // this will store number of bytes actually read
        NULL // not using overlapped IO
    );
 
    if (result) {
        buffer[numBytesRead / sizeof(wchar_t)] = '\0'; // null terminate the string
       std::cout << "Number of bytes read: " << numBytesRead << std::endl;
        std::cout << "Message: " << buffer << std::endl;
    } else {
        std::cout << "Failed to read data from the pipe." << std::endl;
    }*/
}
//------------------------------------------------------------------------------------------------------------------
Data Client::readData(){
	std::string name;
	unsigned int number;
	std::cout << "Enter a name: " << std::endl;
	std::cin>> name;
	std::cout << "Enter a ID: " << std::endl;
	std::cin>> number;
	Data item(name,number);
	return item; 
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
        GENERIC_READ, // only need read access
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
}

//------------------------------------------------------------------------------------------------------------------
bool Client::sendData(){

}


//------------------------------------------------------------------------------------------------------------------
bool Client::openConnection() {
	std::cout << "Connecting to server..." << std::endl; 
    if (Client::getPipe() == INVALID_HANDLE_VALUE) {
        std::cout << "Failed ." << std::endl;
        return false;
    }
    return true;
}


//------------------------------------------------------------------------------------------------------------------
unsigned int Client::authKeyGenerator(){
	srand (time(NULL));
	return 2 * ( rand() % INT_MAX );  //Generate only even keys for client validation
}

//------------------------------------------------------------------------------------------------------------------
main () {
	Client c("ProgramPipe");
	c.readData();
}
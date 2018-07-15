#include <iostream>
#include "Server.hpp"


//------------------------------------------------------------------------------------------------------------------
void Server::setPipe(){
    this->currentPipe = CreateNamedPipe(
        (pipePrefix + Server::getPipeName()).c_str(), // name of the pipe
        PIPE_ACCESS_OUTBOUND, // 1-way pipe -- send only
        PIPE_TYPE_BYTE, // send data as a byte stream
        1, // only allow 1 instance of this pipe
        0, // no outbound buffer
        0, // no inbound buffer
        0, // use default wait time
        NULL // use default security attributes
    );
}


//------------------------------------------------------------------------------------------------------------------
void Server::insertItemOnList(Data item){
    this->itemList.push_back(item);
}

//------------------------------------------------------------------------------------------------------------------
bool Server::startServer(){
    std::cout << "Initializing " << "pipe name: " << Server::getPipeName()<< std::endl;
    Server::setPipe(); 
    if (Server::getPipe() == NULL || Server::getPipe() == INVALID_HANDLE_VALUE) {
        std::cout << "Failed to pipe" << std::endl;
        system("pause");
        return false;
    }

    std::cout << "Waiting for pipe connections" << std::endl;
    while (Server::getPipe() != INVALID_HANDLE_VALUE){
        if (ConnectNamedPipe(Server::getPipe(), NULL)){

        }
    }
 
}

//------------------------------------------------------------------------------------------------------------------
Server::~Server(){
    CloseHandle(Server::getPipe()); 
    std::cout << "Connection closed" << std::endl; 
    system("pause");
}

//------------------------------------------------------------------------------------------------------------------
bool Server::validateClient(const unsigned int authKey){
    if (authKey % 2 == 0) {
        std::cout << "Client with Auth Key "<< authKey << " connected" << std::endl;
        return true;
    }
    else {
        std::cout <<"Connection denied for the client with Auth Key" << authKey << std::endl;
        return false;
    }
}

//------------------------------------------------------------------------------------------------------------------
main () {
	Server s(std::string("ProgramPipe"));
	s.startServer();
}

//------------------------------------------------------------------------------------------------------------------
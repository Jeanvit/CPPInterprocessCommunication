#include <iostream>
#include <vector>
#include "Server.hpp"

//------------------------------------------------------------------------------------------------------------------
void Server::setPipe(){
    this->currentPipe = CreateNamedPipe(
        (pipePrefix + Server::getPipeName()).c_str(), 
        PIPE_ACCESS_DUPLEX, 
        PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT, 
        10,
        0, 
        0, 
        NMPWAIT_USE_DEFAULT_WAIT, 
        NULL 
    );
}

//------------------------------------------------------------------------------------------------------------------
void Server::insertItemOnList(Data item){
    this->itemList.push_back(item);
}
//------------------------------------------------------------------------------------------------------------------
void Server::sendAllData(){
    std::vector<Data> serverData = Server::getItemList();
     while (!serverData.empty()){   
        std::cout << serverData.back() << std::endl; 
        Server::writePipeData(serverData.back().toString());
        serverData.pop_back();
    }
    Server::writePipeData("");
}

//------------------------------------------------------------------------------------------------------------------
bool Server::startServer(){
    std::cout << "Initializing " << "pipe name: " << Server::getPipeName()<< std::endl;
    Server::setPipe(); 
    if (Server::getPipe() == NULL || Server::getPipe() == INVALID_HANDLE_VALUE) {
        std::cout << "Failed!" << std::endl;
        system("pause");
        return false;
    }

    std::cout << "Waiting for pipe client connections" << std::endl;
        if (ConnectNamedPipe(Server::getPipe(), NULL)){
            if (Server::validateClient(atoi(Server::readPipeData().c_str()))){
                Server::writePipeData("1");
                    while (Server::getPipe() != INVALID_HANDLE_VALUE){
                        int option = atoi(Server::readPipeData().c_str());
                        switch (option){
                            case 1:{
                                std::cout << "A client is writing data"<< std::endl;
                                Data data = Server::readPipeData();
                                Server::insertItemOnList(data);
                                std::cout << "New data: " << data << std::endl; 
                                break;
                            }
                            case 2:{
                                std::cout << "A client requested all data"<< std::endl;
                                Server::sendAllData();
                                break;
                            }
                        }

                    }
            }
            else Server::writePipeData("0");
        }
}

//------------------------------------------------------------------------------------------------------------------ 

std::string Server::readPipeData(){
    char buffer[256];
    DWORD numBytesRead = 0;
    BOOL result = ReadFile(
        Server::getPipe(),
        buffer, 
        127 * sizeof(char), 
        &numBytesRead, 
        NULL 
    );
 
    if (result) {
        buffer[numBytesRead / sizeof(char)] = '\0'; 
        //std::cout << "Bytes read: " << numBytesRead << std::endl;
        //std::cout << "Message: " << buffer << std::endl;
    } else {
       // std::cout << "Failed to read data from the pipe." << std::endl;
    }
    return std::string(buffer);
}

//------------------------------------------------------------------------------------------------------------------
bool Server::writePipeData(const std::string& data){
    BOOL result = ConnectNamedPipe(Server::getPipe(), NULL);
    DWORD numBytesWritten = 0;
    result = WriteFile(
        Server::getPipe(),
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
Server::~Server(){
    CloseHandle(Server::getPipe()); 
    std::cout << "Connection closed" << std::endl; 
    system("pause");
}

//------------------------------------------------------------------------------------------------------------------
bool Server::validateClient(const int authKey){
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
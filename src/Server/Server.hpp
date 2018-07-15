#ifndef SRC_SERVER_HPP
#define SRC_SERVER_HPP

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include "../Data/Data.hpp"

const std::string pipePrefix = "\\\\.\\pipe\\";

class Server {

private:
	const std::string pipeName;
	HANDLE currentPipe;
	std::vector<Data> itemList;
public:
	Server (const std::string& Name): pipeName(Name) {};
	~Server();
	bool startServer() ;
	bool validateClient(const unsigned int authKey);
	bool openConnection();
	void setPipe();
	void insertItemOnList(Data item);
	inline HANDLE getPipe() const { return currentPipe; };
	inline std::string getPipeName() const { return pipeName; };
};


#endif /*  SRC_SERVER_HPP   */
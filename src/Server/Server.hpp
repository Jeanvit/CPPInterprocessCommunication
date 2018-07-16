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
	~Server();
	Server (const std::string& Name): pipeName(Name) {};
	bool startServer() ;
	bool validateClient(const int authKey);
	bool writePipeData(const std::string& data);
	bool openConnection();
	void setPipe();
	void sendAllData();
	void insertItemOnList(Data item);
	std::string readPipeData();
	inline HANDLE getPipe() const { return currentPipe; };
	inline std::vector<Data> getItemList() const { return itemList; };
	inline std::string getPipeName() const { return pipeName; };
};


#endif /*  SRC_SERVER_HPP   */
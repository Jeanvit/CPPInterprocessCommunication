#ifndef SRC_CLIENT_HPP
#define SRC_CLIENT_HPP

#include <windows.h>
#include <iostream>
#include "../Data/Data.hpp"

const std::string pipePrefix = "\\\\.\\pipe\\";

class Client {
private:
	const std::string pipeName;
	HANDLE currentPipe;
	unsigned int authKey;
public:
	unsigned int authKeyGenerator();
	Client (const std::string& clientName);
	~Client(); 
	Data readData();
	std::string readPipeData();
	void readAllServerData();
	void requestServerAction(const unsigned int option);
	void setPipe();
	bool writePipeData(const std::string& data);
	bool authenticate();
	bool openConnection();
	inline std::string getPipeName() const { return pipeName; };
	inline unsigned int getAuthKey() const { return authKey; };
	inline HANDLE getPipe() const { return currentPipe; }

};


#endif /*  SRC_CLIENT_HPP   */
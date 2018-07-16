#ifndef SRC_DATA_HPP
#define SRC_DATA_HPP

#include <iostream>
#include <string>

class Data {
private:
	std::string dataName;

public:
	Data (const std::string& name): dataName(name) {};
	inline std::string getDataName() const { return this->dataName; };
	inline std::string toString() const { return this->dataName; };
	
	friend std::ostream& operator<<(std::ostream& os, const Data& data)  {   os << data.dataName; return os; } ;  
	void operator= ( std::string name ) { dataName = name; };
};


#endif /*  SRC_DATA_HPP   */
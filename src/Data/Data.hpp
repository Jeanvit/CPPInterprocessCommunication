#ifndef SRC_DATA_HPP
#define SRC_DATA_HPP

#include <iostream>
#include <string>

/* add template */

class Data {
private:
	const std::string dataName;
	const unsigned int id;

public:
	Data (const std::string& name, const unsigned int number): dataName(name), id(number)  { std::cout << "Created " << dataName << " data. " << std::endl; };
	inline std::string getDataName() const { return this->dataName; };
	inline unsigned int getId() const { return this->id; };
};


#endif /*  SRC_DATA_HPP   */
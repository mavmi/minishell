#include <iostream>
#include <string>

class Debugger {
public:
	Debugger(const std::string& name)
		: name(name) {
		std::cout << "\t***** BEGIN OF " << name << " *****" << std::endl;
	}

	~Debugger(){
		std::cout << "\t***** END OF " << name << " *****" << std::endl;
	}

private:
	std::string name;

};
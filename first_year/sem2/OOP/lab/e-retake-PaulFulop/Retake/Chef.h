#pragma once
#include <string>
class Chef{
public:

	std::string name, speciality;
	Chef() = default;
	Chef(const std::string& name, const std::string& speciality)
		: name(name), speciality(speciality)
	{}

	friend std::istream& operator >> (std::istream& is, Chef& c);
	friend std::ostream& operator << (std::ostream& os, const Chef& c);
};


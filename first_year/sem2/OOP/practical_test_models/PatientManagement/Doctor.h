#pragma once
#include <string>

class Doctor{
public:
	std::string name, specialisation;

	Doctor() = default;

	Doctor(const std::string& name, const std::string& specialisation)
		: name(name), specialisation(specialisation)
	{}

	friend std::istream& operator >> (std::istream& is, Doctor& d);
	friend std::ostream& operator << (std::ostream& os, const Doctor& d);

};


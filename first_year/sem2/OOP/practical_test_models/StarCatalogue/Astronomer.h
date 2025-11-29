#pragma once
#include <string>

class Astronomer {
public:
	std::string name, constellation;


	Astronomer() = default;

	Astronomer(const std::string& name, const std::string& constellation)
		: name(name), constellation(constellation)
	{
	}

	friend std::istream& operator >> (std::istream& is, Astronomer& a);
	friend std::ostream& operator << (std::ostream& os, const Astronomer& a);
};
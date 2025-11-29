#pragma once
#include <string>

class Researcher{
public:
	std::string name, position;

	Researcher() = default;

	Researcher(const std::string& name, const std::string& position)
		: name(name), position(position)
	{}

	friend std::istream& operator >> (std::istream& is, Researcher& r);
	friend std::ostream& operator << (std::ostream& os, const Researcher& r);
	bool IsSenior() const;
};


#pragma once
#include <string>
#include <vector>

class Star {
public:
	std::string name, constellation;
	int RA, Dec, diameter;



	Star() = default;

	Star(const std::string& name, const std::string& constellation, int RA, int Dec, int diameter)
		: name(name), constellation(constellation), RA(RA), Dec(Dec), diameter(diameter)
	{}

	std::string ToString() const;
	friend std::istream& operator >> (std::istream& is, Star& s);
	friend std::ostream& operator << (std::ostream& os, const Star& s);
};
#pragma once
#include <string>
#include <vector>

class Biologist {
public:
	std::string name;
	std::vector<std::string> species;



	Biologist() = default;

	Biologist(const std::string& name, const std::vector<std::string>& species)
		: name(name), species(species)
	{}

	bool operator == (const Biologist& other) { return name == other.name; }

	friend std::istream& operator >> (std::istream& is, Biologist& b);
	friend std::ostream& operator << (std::ostream& os, const Biologist& b);
};
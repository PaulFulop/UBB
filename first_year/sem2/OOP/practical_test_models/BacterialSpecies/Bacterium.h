#pragma once
#include <string>
#include <vector>

class Bacterium {
public:
	std::string name, species;
	int size;
	std::vector<std::string> diseases;

	Bacterium() = default;

	Bacterium(const std::string& name, const std::string& species, int size, const std::vector<std::string>& diseases)
		: name(name), species(species), size(size), diseases(diseases)
	{}

	bool operator == (const Bacterium& other) { return name == other.name; }
	std::string ToString() const;
	friend std::istream& operator >> (std::istream& is, Bacterium& b);
	friend std::ostream& operator << (std::ostream& os, const Bacterium& b);
};
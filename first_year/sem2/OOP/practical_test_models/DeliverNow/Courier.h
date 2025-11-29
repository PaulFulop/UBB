#pragma once
#include <string>
#include <vector>

class Courier {
public:
	std::string name;
	std::vector<std::string> streets;
	double x, y, radius;

	Courier() = default;
	Courier(const std::string& name, const std::vector<std::string>& streets, double x, double y, double radius)
		: name(name), streets(streets), x(x), y(y), radius(radius){}

	friend std::istream& operator >> (std::istream& is, Courier& c);
	friend std::ostream& operator << (std::ostream& os, const Courier& c);
};
#include "Courier.h"
#include "Utils.h"

std::istream& operator >> (std::istream& is, Courier& c) {
	std::string line;
	std::getline(is, line);
	std::vector<std::string> tokens = Tokenize(line, ';');
	if (tokens.size() != 5)
		return is;

	std::string name = tokens[0];
	std::vector<std::string> streets = Tokenize(tokens[1], ',');
	double x = std::atof(tokens[2].c_str());
	double y = std::atof(tokens[3].c_str());
	double rad = std::atof(tokens[4].c_str());
	c = Courier(name, streets, x, y, rad);
	return is;
}

std::ostream& operator << (std::ostream& os, const Courier& c) {
	os << c.name << ';';
	for (const auto& str : c.streets)
		os << str << ',';
	os << c.x << ',' << c.y << ',' << c.radius;

	return os;
}
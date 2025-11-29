#include "Chef.h"
#include "Utils.h"

std::istream& operator >> (std::istream& is, Chef& c) {
	std::string line;
	std::getline(is, line);
	auto tokens = Tokenize(line, ',');
	if (tokens.size() != 2) return is;

	c = Chef(tokens[0], tokens[1]);
	return is;
}

std::ostream& operator << (std::ostream& os, const Chef& c) {
	os << c.name << ',' << c.speciality;
	return os;
}
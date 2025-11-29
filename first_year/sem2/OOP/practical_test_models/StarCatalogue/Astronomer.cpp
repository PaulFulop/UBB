#include "Astronomer.h"
#include "Utils.h"

std::istream& operator >> (std::istream& is, Astronomer& a) {
	std::string line;
	std::getline(is, line);
	std::vector<std::string> tokens = Tokenize(line, ',');
	if (tokens.size() != 2)
		return is;

	a = Astronomer(tokens[0], tokens[1]);
	return is;
}

std::ostream& operator << (std::ostream& os, const Astronomer& a) {
	os << a.name << ',' << a.constellation;
	return os;
}
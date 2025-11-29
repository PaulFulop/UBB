#include "Star.h"
#include "Utils.h"

std::string Star::ToString() const {
	return name + ", " + constellation + ", " + std::to_string(RA) + ", " + std::to_string(Dec) + ", " + std::to_string(diameter);
}

std::istream& operator >> (std::istream& is, Star& s) {
	std::string line;
	std::getline(is, line);
	std::vector<std::string> tokens = Tokenize(line, ',');
	if (tokens.size() != 5)
		return is;

	s = Star(tokens[0], tokens[1], std::atoi(tokens[2].c_str()), std::atoi(tokens[3].c_str()), std::atoi(tokens[4].c_str()));
	return is;
}

std::ostream& operator << (std::ostream& os, const Star& s) {
	os << s.name << ',' << s.constellation << ',' << s.RA << ',' << s.Dec << ',' << s.diameter;
	return os;
}
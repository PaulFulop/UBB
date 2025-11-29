#include "Doctor.h"
#include "Utils.h"

std::istream& operator >> (std::istream& is, Doctor& d) {
	std::string line;
	std::getline(is, line);
	auto tokens = Tokenize(line, ',');

	if (tokens.size() != 2) return is;

	d = Doctor(tokens[0], tokens[1]);
	return is;
}

std::ostream& operator << (std::ostream& os, const Doctor& d) {
	os << d.name << ',' << d.specialisation;
	return os;
}
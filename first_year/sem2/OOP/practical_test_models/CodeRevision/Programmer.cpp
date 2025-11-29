#include "Programmer.h"
#include "Utils.h"

std::istream& operator >> (std::istream& is, Programmer& p) {
	std::string line;
	std::getline(is, line);
	auto tokens = Tokenize(line, ',');
	if (tokens.size() != 3) return is;

	p = Programmer(tokens[0], std::atoi(tokens[1].c_str()), std::atoi(tokens[2].c_str()));
	return is;
}

std::ostream& operator << (std::ostream& os, const Programmer& p) {
	os << p.name << ',' << p.revisedFiles << ',' << p.filesToRevise;
	return os;
}
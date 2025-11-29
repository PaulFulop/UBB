#include "Biologist.h"
#include "Utils.h"

std::istream& operator >> (std::istream& is, Biologist& b) {
	std::string line;
	std::getline(is, line);

	std::vector<std::string> tokens = Tokenize(line, ';');
	if (tokens.size() != 2) return is;

	b = Biologist(tokens[0], Tokenize(tokens[1], ','));
	return is;
}

std::ostream& operator << (std::ostream& os, const Biologist& b) {
	os << b.name + ';';

	int i;
	for (i = 0; i < b.species.size() - 1; ++i)
		os << b.species[i] << ',';
	os << b.species[i] << '\n';
	return os;
}
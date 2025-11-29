#include "Writer.h"
#include "Utils.h"

std::istream& operator >> (std::istream& is, Writer& w) {
	std::string line;
	std::getline(is, line);
	auto tokens = Tokenize(line, ',');

	if (tokens.size() != 2) return is;

	w = Writer(tokens[0], tokens[1]);
	return is;
}

std::ostream& operator << (std::ostream& os, const Writer& w) {
	os << w.name << ',' << w.expertise;
	return os;
}
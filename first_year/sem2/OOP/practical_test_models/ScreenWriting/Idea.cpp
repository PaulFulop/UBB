#include "Idea.h"
#include "Utils.h"

std::istream& operator >> (std::istream& is, Idea& i) {
	std::string line;
	std::getline(is, line);
	auto tokens = Tokenize(line, ',');

	if (tokens.size() != 4) return is;

	i = Idea(tokens[0], tokens[1], tokens[2], std::atoi(tokens[3].c_str()));
	return is;
}

std::ostream& operator << (std::ostream& os, const Idea& i) {
	os << i.desc << ',' << i.status << ',' << i.creator << ',' << i.act;
	return os;
}
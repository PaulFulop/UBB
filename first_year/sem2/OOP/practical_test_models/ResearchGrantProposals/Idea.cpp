#include "Idea.h"
#include "Utils.h"


std::istream& operator >> (std::istream& is, Idea& i) {
	std::string line;
	std::getline(is, line);
	auto tokens = Tokenize(line, ',');

	if (tokens.size() != 5) return is;

	i = Idea(tokens[0], tokens[1], tokens[2], tokens[3], std::atoi(tokens[4].c_str()));
	return is;
}

std::ostream& operator << (std::ostream& os, const Idea& i) {
	os << i.title << ',' << i.description << ',' << i.status << ',' << i.creator << ',' << i.duration;
	return os;
}
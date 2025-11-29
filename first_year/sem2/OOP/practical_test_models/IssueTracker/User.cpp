#include "User.h"
#include "Utils.h"

std::istream& operator >> (std::istream& is, User& u) {
	std::string line;
	std::getline(is, line);
	auto tokens = Tokenize(line, ',');

	if (tokens.size() != 2) return is;

	u = User(tokens[0], tokens[1]);
	return is;
}

std::ostream& operator << (std::ostream& os, const User& u) {
	os << u.name << ',' << u.type;
	return os;
}
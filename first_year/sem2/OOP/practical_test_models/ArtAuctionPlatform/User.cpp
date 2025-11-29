#include "User.h"

std::istream& operator >> (std::istream& is, User& u) {
	std::string line;
	std::getline(is, line);

	std::vector<std::string> tokens = Tokenize(line, ';');

	if (tokens.size() != 3) return is;

	u = User(tokens[0], std::atoi(tokens[1].c_str()), tokens[2]);
	return is;
}

std::ostream& operator << (std::ostream& os, const User& u) {
	os << u.name << ';' + std::to_string(u.id) << ';' + u.type + '\n';
	return os;
}
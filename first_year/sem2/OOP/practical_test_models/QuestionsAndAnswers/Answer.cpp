#include "Answer.h"

std::istream& operator >> (std::istream& is, Answer& a) {
	std::string line;
	std::getline(is, line);
	auto tokens = Tokenize(line, ',');

	if (tokens.size() != 5) return is;
	a = Answer(std::atoi(tokens[0].c_str()), std::atoi(tokens[1].c_str()), tokens[2], tokens[3], std::atoi(tokens[4].c_str()));
	return is;
}

std::ostream& operator << (std::ostream& os, const Answer& a) {
	os << a.id << ',' << a.qId << ',' << a.name << ',' << a.text << ',' << a.votes;
	return os;
}

std::string Answer::ToString() const {
	return std::to_string(id) + ", " + name + ", " + text + ", " + std::to_string(votes);
}
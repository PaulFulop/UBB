#include "Domain.h"
#include "Utils.h"

Participant::Participant() : name(""), score(0){}

Participant::Participant(std::string _name, int _score): name (_name), score (_score) {}

std::istream& operator >> (std::istream& is, Participant& p) {
	std::string participantString;
	getline(is, participantString);

	std::vector<std::string> tokens = Tokenize(participantString, ',');

	if (tokens.size() != 2)
		return is;

	Participant participantCopy = Participant(tokens[0], std::atoi(tokens[1].c_str()));
	p = participantCopy;
	return is;
}

std::ostream& operator << (std::ostream& os, const Participant& p) {
	os << p.name << "," << p.score;
	return os;
}
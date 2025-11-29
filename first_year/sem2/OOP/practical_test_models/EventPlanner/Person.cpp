#include "Person.h"
#include "Utils.h"
#include <cmath>

std::istream& operator >> (std::istream& is, Person& p) {
	std::string line;
	std::getline(is, line);
	auto tokens = Tokenize(line, ',');
	if (tokens.size() != 4) return is;

	p = Person(tokens[0], std::atoi(tokens[1].c_str()), std::atoi(tokens[2].c_str()), (tokens[3] == "false" ? false : true));
	return is;
}

std::ostream& operator << (std::ostream& os, const Person& p) {
	os << p.name << ',' << p.latitude << ',' << p.longitude << ',' << (p.organiser ? "true" : "false");
	return os;
}

bool Person::NearEvent(int x, int y) const {
	return std::sqrt((x - latitude) * (x - latitude) + (y - longitude) * (y - longitude)) <= 5;
}

bool Person::IsOrganiser() const {
	return organiser;
}
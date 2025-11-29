#include "Department.h"
#include "Utils.h"

std::istream& operator >> (std::istream& is, Department& d) {
	std::string line;
	std::getline(is, line);

	std::vector<std::string> tokens = Tokenize(line, ',');

	if (tokens.size() != 2)
		return is;

	d = Department(tokens[0], tokens[1]);
	return is;
}

std::ostream& operator << (std::ostream& os, const Department& d) {
	os << d.name << ',' << d.desc;
	return os;
}

std::string Department::ToString() const {
	return name + " " + desc;
}
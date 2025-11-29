#include "Patient.h"
#include "Utils.h"

std::istream& operator >> (std::istream& is, Patient& p) {
	std::string line;
	std::getline(is, line);
	auto tokens = Tokenize(line, ',');

	if (tokens.size() != 5) return is;

	p = Patient(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4]);
	return is;
}

std::ostream& operator << (std::ostream& os, const Patient& p) {
	os << p.name << ',' << p.diagnosis << ',' << p.specialisation << ',' << p.doctor << ',' << p.admissionDate;
	return os;
}

std::string Patient::ToString() const {
	return name + ", " + diagnosis + ", " + admissionDate;
}
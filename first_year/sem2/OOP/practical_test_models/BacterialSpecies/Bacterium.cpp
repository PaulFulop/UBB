#include "Bacterium.h"
#include "Utils.h"

std::string Bacterium::ToString() const {
	return name + ", " + species + ", " + std::to_string(size);
}

std::istream& operator >> (std::istream& is, Bacterium& b) {
	std::string line;
	std::getline(is, line);

	std::vector<std::string> tokens = Tokenize(line, ';');
	if (tokens.size() != 4) return is;

	b = Bacterium(tokens[0], tokens[1], std::atoi(tokens[2].c_str()), Tokenize(tokens[3], ','));
	return is;
}

std::ostream& operator << (std::ostream& os, const Bacterium& b) {
	os << b.name + ';' + b.species + ';' + std::to_string(b.size) + ';';
	int i;
	for (i = 0; i < b.diseases.size() - 1; ++i)
		os << b.diseases[i] + ',';
	os << b.diseases[i] + '\n';
	return os;
}
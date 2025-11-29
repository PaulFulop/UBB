#include "SourceFile.h"
#include "Utils.h"

std::istream& operator >> (std::istream& is, SourceFile& s) {
	std::string line;
	std::getline(is, line);
	auto tokens = Tokenize(line, ',');
	if (tokens.size() != 4) {
		if (tokens.size() == 3) {
			s = SourceFile(tokens[0], tokens[1], tokens[2], "");
			return is;
		}
		return is;
	}
	s = SourceFile(tokens[0], tokens[1], tokens[2], tokens[3]);
	return is;
}

std::ostream& operator << (std::ostream& os, const SourceFile& s) {
	os << s.name << ',' << s.status << ',' << s.creator << ',' << s.reviewer;
	return os;
}

std::string SourceFile::ToString() const {
	return name + ", " + status + ", " + creator + ", " + reviewer;
}
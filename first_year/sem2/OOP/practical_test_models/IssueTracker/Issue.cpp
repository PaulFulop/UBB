#include "Issue.h"
#include "Utils.h"

std::istream& operator >> (std::istream& is, Issue& i){
	std::string line;
	std::getline(is, line);
	auto tokens = Tokenize(line, ',');

	if (tokens.size() != 4) {
		if (tokens.size() == 3) {
			i = Issue(tokens[0], (tokens[1] == "open" ? true : false), tokens[2], "");
			return is;
		}
		return is;
	}

	i = Issue(tokens[0], (tokens[1] == "open" ? true : false), tokens[2], tokens[3]);
	return is;
}

std::ostream& operator << (std::ostream& os, const Issue& i) {
	os << i.desc << ',' << (i.status ? "open" : "closed") << ',' << i.reporter << ',' << i.solver;
	return os;
}

std::string Issue::ToString() const {
	return desc + ", " + (status ? "open" : "closed") + ", " + reporter + ", " + solver;
}
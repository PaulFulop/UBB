#include "Report.h"
#include "Utils.h"

std::istream& operator >> (std::istream& is, Report& r) {
	std::string line;
	std::getline(is, line);

	auto tokens = Tokenize(line, ',');
	if (tokens.size() != 5) return is;

	r = Report(tokens[0], tokens[1], std::atoi(tokens[2].c_str()), std::atoi(tokens[3].c_str()), (tokens[4] == "false" ? false : true));
	return is;
}

std::ostream& operator << (std::ostream& os, const Report& r) {
	os << r.description << ',' << r.reporter << ',' << r.latitude << ',' << r.longitude << ',' << (r.valid ? "true" : "false") << '\n';
	return os;
}

std::string Report::ToString() const {
	return description + ", " + reporter + ", " + (valid ? "validated" : "not validated");
}
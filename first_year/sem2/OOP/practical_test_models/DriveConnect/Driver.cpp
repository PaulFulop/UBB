#pragma once
#include "Driver.h"
#include "Utils.h"
#include <cmath>

std::istream& operator >> (std::istream& is, Driver& d) {
	std::string line;
	std::getline(is, line);

	auto tokens = Tokenize(line, ',');
	if (tokens.size() != 4) return is;

	d = Driver(tokens[0], std::atoi(tokens[1].c_str()), std::atoi(tokens[2].c_str()), std::atoi(tokens[3].c_str()));
	return is;
}

std::ostream& operator << (std::ostream& os, const Driver& d) {
	os << d.name << ',' << d.latitude << ',' << d.longitude << ',' << d.score << '\n';
	return os;
}

bool Driver::isInRegionOfInterest(int x, int y, int dist) const {
	return sqrt((x - latitude) * (x - latitude) - (y - longitude) * (y - longitude)) <= dist;
}
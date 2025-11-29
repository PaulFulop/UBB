#pragma once
#include <string>

class Driver {
public:
	std::string name;
	int latitude, longitude, score;

	Driver() = default;

	Driver(const std::string& name, int latitude, int longitude, int score)
		: name(name), latitude(latitude), longitude(longitude), score(score)
	{}

	friend std::istream& operator >> (std::istream& is, Driver& d);
	friend std::ostream& operator << (std::ostream& os, const Driver& d);
	bool isInRegionOfInterest(int x, int y, int dist) const;
};
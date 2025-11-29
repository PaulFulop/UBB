#pragma once
#include <string>

class Report{
public:
	std::string description, reporter;
	int latitude, longitude;
	bool valid;

	Report() = default;
	Report(const std::string& description, const std::string& reporter, int latitude, int longitude, bool valid)
		: description(description), reporter(reporter), latitude(latitude), longitude(longitude), valid(valid)
	{}

	friend std::istream& operator >> (std::istream& is, Report& r);
	friend std::ostream& operator << (std::ostream& os, const Report& r);
	std::string ToString() const;
};


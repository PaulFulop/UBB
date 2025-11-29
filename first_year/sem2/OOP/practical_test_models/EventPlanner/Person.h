#pragma once
#include <string>

class Person{
public:
	std::string name;
	int latitude, longitude;
	bool organiser;

	Person() = default;
	Person(const std::string& name, int latitude, int longitude, bool organiser)
		: name(name), latitude(latitude), longitude(longitude), organiser(organiser)
	{}

	friend std::istream& operator >> (std::istream& is, Person& p);
	friend std::ostream& operator << (std::ostream& os, const Person& p);
	bool NearEvent(int x, int y) const;
	bool IsOrganiser() const;
	bool operator == (const Person& other) {
		return name == other.name && latitude == other.latitude && longitude == other.longitude && organiser == other.organiser;
	}
};


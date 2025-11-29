#pragma once
#include <string>

class Event{
public:
	std::string organiser, name, desc;
	int latitude, longitude;
	std::string date;

	Event() = default;
	Event(const std::string& organiser, const std::string& name, const std::string& desc, int latitude, int longitude, const std::string& date)
		: organiser(organiser), name(name), desc(desc), latitude(latitude), longitude(longitude), date(date)
	{}

	friend std::istream& operator >> (std::istream& is, Event& e);
	friend std::ostream& operator << (std::ostream& os, const Event& e);
	std::string ToString() const;
	bool operator == (const Event& other) {
		return name == other.name && latitude == other.latitude && longitude == other.longitude;
	}
};


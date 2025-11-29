#include "Event.h"
#include "Utils.h"

std::istream& operator >> (std::istream& is, Event& e) {
	std::string line;
	std::getline(is, line);
	auto tokens = Tokenize(line, ',');

	if (tokens.size() != 6) return is;

	e = Event(tokens[0], tokens[1], tokens[2], std::atoi(tokens[3].c_str()), std::atoi(tokens[4].c_str()), tokens[5]);
	return is;
}

std::ostream& operator << (std::ostream& os, const Event& e) {
	os << e.organiser << ',' << e.name << ',' << e.desc << ',' << e.latitude << ',' << e.longitude << ',' << e.date;
	return os;
}

std::string Event::ToString() const{ 
	return organiser + ", " + name + ", " + std::to_string(latitude) + ", " + std::to_string(longitude) + ", " + date;
}
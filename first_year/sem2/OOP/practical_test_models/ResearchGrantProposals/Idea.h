#pragma once
#include <string>

class Idea{
public:
	std::string title, description, status, creator;
	int duration;



	Idea() = default;

	Idea(const std::string& title, const std::string& description, const std::string& status, const std::string& creator, int duration)
		: title(title), description(description), status(status), creator(creator), duration(duration)
	{
	}

	friend std::istream& operator >> (std::istream& is, Idea& i);
	friend std::ostream& operator << (std::ostream& os, const Idea& i);
	bool operator == (Idea& other) {
		return title == other.title && description == other.description && status == other.status && creator == other.creator && duration == other.duration;
	}
};


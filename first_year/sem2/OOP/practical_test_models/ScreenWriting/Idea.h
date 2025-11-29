#pragma once
#include <string>

class Idea{
public:
	std::string desc, status, creator;
	int act;

	Idea() = default;
	Idea(const std::string& desc, const std::string& status, const std::string& creator, int act)
		: desc(desc), status(status), creator(creator), act(act)
	{}
	
	friend std::istream& operator >> (std::istream& is, Idea& i);
	friend std::ostream& operator << (std::ostream& os, const Idea& i);
	bool operator == (const Idea& other) {
		return act == other.act && desc == other.desc;
	}
};


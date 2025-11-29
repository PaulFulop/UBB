#pragma once
#include <string>

class User {
public:
	std::string name, type;

	User() = default;

	User(const std::string& name, const std::string& type)
		: name(name), type(type)
	{}

	friend std::istream& operator >> (std::istream& is, User& u);
	friend std::ostream& operator << (std::ostream& os, const User& u);
};


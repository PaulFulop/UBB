#pragma once
#include <string>

class User{
public:
	std::string name;

	User() = default;

	User(const std::string& name)
		: name(name)
	{
	}

	friend std::istream& operator >> (std::istream& is, User& u);
	friend std::ostream& operator << (std::ostream& os, const User& u);
};


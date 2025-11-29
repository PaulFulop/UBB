#pragma once
#include <string>
#include "Utils.h"

class User {
public:
	std::string name;
	int id;
	std::string type;
	User() = default;
	User(const std::string& name, int id, const std::string& type)
		: name(name), id(id), type(type)
	{}

	friend std::istream& operator >> (std::istream& is, User& u);
	friend std::ostream& operator << (std::ostream& os, const User& u);
};
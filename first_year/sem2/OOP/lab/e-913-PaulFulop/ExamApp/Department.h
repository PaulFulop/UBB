#pragma once
#include <string>
#include <vector>

class Department {
public:
	std::string name, desc;

	Department() = default;

	Department(const std::string& name, const std::string& desc)
		: name(name), desc(desc)
	{
	}

	friend std::istream& operator >> (std::istream& is, Department& d);
	friend std::ostream& operator << (std::ostream& os, const Department& d);
	std::string ToString() const;
};
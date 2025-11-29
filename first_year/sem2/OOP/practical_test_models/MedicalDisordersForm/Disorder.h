#pragma once
#include <string>
#include <vector>

class Disorder {
public:
	std::string category, name;
	std::vector<std::string> symptoms;

	Disorder();
	Disorder(std::string _category, std::string _name, std::vector<std::string> _symptoms);
	std::string ToString();
};
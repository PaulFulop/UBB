#include "Disorder.h"


Disorder::Disorder(): name(""), category(""), symptoms(std::vector<std::string>()){}
Disorder::Disorder(std::string _category, std::string _name, std::vector<std::string> _symptoms): category(_category), name(_name), symptoms(_symptoms) {}
std::string Disorder::ToString() {
	return category + " | " + name;
}
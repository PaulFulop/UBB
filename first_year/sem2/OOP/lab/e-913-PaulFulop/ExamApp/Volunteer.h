#pragma once
#include <string>
#include <vector>
#include "Department.h"

class Volunteer{
public:
	std::string name, email;
	std::vector<std::string> listOfInterests;
	Department department;

	Volunteer() = default;

	Volunteer(const std::string& name, const std::string& email, const std::vector<std::string>& listOfInterests, const Department& department)
		: name(name), email(email), listOfInterests(listOfInterests), department(department)
	{
	}

	friend std::istream& operator >> (std::istream& is, Volunteer& v);
	friend std::ostream& operator << (std::ostream& os, const Volunteer& v);
	double SuitabilityScore();
	std::string ToString();
};


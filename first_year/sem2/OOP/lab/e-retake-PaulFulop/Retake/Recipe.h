#pragma once
#include <string>
#include <vector>

class Recipe{
public:
	std::string name, cuisine;
	int prep;
	std::vector<std::string> ingredients;

	Recipe() = default;
	Recipe(const std::string& name, const std::string& cuisine, int prep, const std::vector<std::string>& ingredients)
		: name(name), cuisine(cuisine), prep(prep), ingredients(ingredients)
	{}

	friend std::istream& operator >> (std::istream& is, Recipe& r);
	friend std::ostream& operator << (std::ostream& os, const Recipe& r);
	std::string ToString() const;
};


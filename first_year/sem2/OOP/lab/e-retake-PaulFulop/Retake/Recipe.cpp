#include "Recipe.h"
#include "Utils.h"

std::istream& operator >> (std::istream& is, Recipe& r) {
	std::string line;
	std::getline(is, line);
	auto tokens = Tokenize(line, ';');
	if (tokens.size() != 4) return is;

	r = Recipe(tokens[0], tokens[1], std::atoi(tokens[2].c_str()), Tokenize(tokens[3], ','));
	return is;
}

std::ostream& operator << (std::ostream& os, const Recipe& r) {
	os << r.name << ';' << r.cuisine << ';' << r.prep << ';';
	int i;
	for (i = 0; i < r.ingredients.size() - 1; ++i)
		os << r.ingredients[i] << ',';
	os << r.ingredients[i];
	return os;
}

std::string Recipe::ToString() const {
	std::string str =  name + ", " + cuisine + ", " + std::to_string(prep) + " minutes, ingredients: ";
	for (const auto& i : ingredients)
		str += i + " ";
	return str;
}
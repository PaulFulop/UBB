#include "Item.h"

std::istream& operator >> (std::istream& is, Item& i) {
	std::string line;
	std::getline(is, line);

	std::vector<std::string> tokens = Tokenize(line, ';');

	if (tokens.size() == 3) {
		i = Item(tokens[0], tokens[1], std::atoi(tokens[2].c_str()), std::vector<std::tuple<int, std::string, int>>());
		return is;
	}
	if (tokens.size() != 4) return is;

	std::vector<std::string> offersTxt = Tokenize(tokens[3], ',');
	std::vector<std::tuple<int, std::string, int>> offers;

	for (const auto& offerTxt : offersTxt) {
		std::vector<std::string> values = Tokenize(offerTxt, ':');
		auto t = std::make_tuple(std::atoi(values[0].c_str()), values[1], std::atoi(values[2].c_str()));
		offers.push_back(t);
	}

	i = Item(tokens[0], tokens[1], std::atoi(tokens[2].c_str()), offers);
	return is;
}

std::ostream& operator << (std::ostream& os, const Item& i) {
	os << i.name << ';' << i.category << ';' + std::to_string(i.price) << ';';
	int k;
	if (!i.offers.size()) {
		os << '\n';
		return os;
	}

	for (k = 0; k < i.offers.size() - 1; ++k) {
		os << std::get<0>(i.offers[k]) << ':' << std::get<1>(i.offers[k]) << ':' << std::get<2>(i.offers[k]) << ',';
	}
	os << std::get<0>(i.offers[k]) << ':' << std::get<1>(i.offers[k]) << ':' << std::get<2>(i.offers[k]) << '\n';

	return os;
}

std::string Item::ToString() const {
	return name + ' ' + category + ' ' + std::to_string(price);
}
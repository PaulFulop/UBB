#pragma once
#include <vector>
#include <string>
#include <tuple>
#include "Utils.h"

class Item {
public:
	std::string name, category;
	int price;
	std::vector<std::tuple<int, std::string, int>> offers;



	Item() = default;

	Item(const std::string& name, const std::string& category, int price, const std::vector<std::tuple<int, std::string, int>>& offers)
		: name(name), category(category), price(price), offers(offers)
	{}

	friend std::istream& operator >> (std::istream& is, Item& i);
	friend std::ostream& operator << (std::ostream& os, const Item& i);
	std::string ToString() const;
};
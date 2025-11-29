#include "Service.h"
#include <algorithm>

void Service::SortRecipes() {
	if (*sorted == false) {
		std::sort(recipes->data.begin(), recipes->data.end(), [](const Recipe& r1, const Recipe& r2) {return (r1.cuisine < r2.cuisine) || (r1.cuisine == r2.cuisine && r1.prep < r2.prep); });
		*sorted = true;
	}
}

std::vector<Recipe> Service::FilterRecipesByCuisine() {
	std::vector<Recipe> filteredRecipes;
	for (const auto& r : recipes->data)
		if (r.cuisine == c.speciality)
			filteredRecipes.push_back(r);

	return filteredRecipes;
}

std::vector<Recipe> Service::FilterByIngredients(std::vector<std::string> ingredients) {
	std::vector<Recipe> filteredRecipes;
	for (const auto& r : recipes->data) {
		bool found = true;
		for(const auto& ingredient : ingredients)
			if (std::find(r.ingredients.begin(), r.ingredients.end(), ingredient) == r.ingredients.end()) {
				found = false;
				break;
			}

		if (found) filteredRecipes.push_back(r);
	}

	return filteredRecipes;
}

void Service::AddRecipe(const Recipe& newR) {
	if (newR.name == "") throw std::exception("Empty name!");
	for (const auto& r : recipes->data)
		if (newR.name == r.name) throw std::exception("Recipe with he same name has been found!");

	recipes->Add(newR);
	*sorted = false;
}
#pragma once
#include "Repo.h"
#include "Chef.h"
#include "Recipe.h"

class Service{
public:
	Chef c;
	Repo<Recipe>* recipes;
	bool* sorted;

	Service() = default;
	Service(const Chef& c, Repo<Recipe>* recipes, bool* sorted)
		: c(c), recipes(recipes), sorted(sorted)
	{}

	void SortRecipes();
	std::vector<Recipe> FilterRecipesByCuisine();
	std::vector<Recipe> FilterByIngredients(std::vector<std::string> ingredients);
	void AddRecipe(const Recipe& newR);
};


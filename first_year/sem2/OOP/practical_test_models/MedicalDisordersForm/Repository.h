#pragma once
#include "Disorder.h"
#include <fstream>
#include <sstream>

class Repository {
public:
	std::vector<Disorder> disorders;
	Repository();
	Repository(std::string fileName);

	Repository FilterByName(std::string name);
	Repository FilterByCategory(std::string category);
	void SortAscendingByCategory();
};
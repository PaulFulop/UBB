#pragma once
#include "Equation.h"
#include <vector>
#include <fstream>
#include <sstream>

class Repository {
public:
	std::vector<Equation> equations;
	Repository();
	Repository(std::string fileName);
	void SortDescendingByGrade();
};
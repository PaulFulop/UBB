#include "Repository.h"

Repository::Repository(): equations(std::vector<Equation>()){}
Repository::Repository(std::string fileName) {
	std::ifstream fin(fileName);

	std::string line;
	std::string coef1, coef2, coef3;
	while (std::getline(fin, line)) {
		std::stringstream ss(line);
		std::getline(ss, coef1, ',');
		std::getline(ss, coef2, ',');
		std::getline(ss, coef3, '\n');
		coef2.erase(0, 1);
		coef3.erase(0, 1);

		equations.push_back(Equation(std::atof(coef1.c_str()), std::atof(coef2.c_str()), std::atof(coef3.c_str())));
	}

	SortDescendingByGrade();
	fin.close();
}

void Repository::SortDescendingByGrade() {
	for (int i = 0; i < equations.size() - 1; ++i)
		for (int j = i + 1; j < equations.size(); ++j)
			if (equations[i].grade < equations[j].grade)
				std::swap(equations[i], equations[j]);
}
#include "Repository.h"

Repository::Repository(): disorders(std::vector<Disorder>()){}
Repository::Repository(std::string fileName) {
	std::ifstream fin(fileName);

	std::string _name, _category, _symptom;
	std::string line;

	while (std::getline(fin, line)){
		std::stringstream ss(line);

		std::getline(ss, _category, '|');
		_category.pop_back();
		std::getline(ss, _name, '|');
		_name.erase(0, 1);
		_name.pop_back();

		std::vector<std::string> _symptoms;
		while (std::getline(ss, _symptom, ',')) {
			if (_symptom[0] == ' ')
				_symptom.erase(0, 1);

			_symptoms.push_back(_symptom);
		}

		disorders.push_back(Disorder(_category, _name, _symptoms));
	}

	fin.close();
}

Repository Repository::FilterByName(std::string name) {
	Repository filteredRepo = Repository();

	for (auto& disorder : disorders) {
		if (disorder.name.find(name) != std::string::npos) {
			filteredRepo.disorders.push_back(disorder);
		}
	}

	return filteredRepo;
}
Repository Repository::FilterByCategory(std::string category) {
	Repository filteredRepo = Repository();

	for (auto& disorder : disorders) {
		if (disorder.category.find(category) != std::string::npos) {
			filteredRepo.disorders.push_back(disorder);
		}
	}

	return filteredRepo;
}

void Repository::SortAscendingByCategory() {
	for(int i = 0; i < disorders.size() - 1; ++i)
		for(int j = i + 1; j < disorders.size(); ++j)
			if (disorders[i].category > disorders[j].category) {
				std::swap(disorders[i], disorders[j]);
			}
}
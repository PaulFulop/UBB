#pragma once
#include "Domain.h"
#include <vector>
#include <sstream>
#include <fstream>

class Repository {
public:
	std::vector<Document> docs;
	Repository();
	Repository(std::string fileName);

	Repository FilterRepo(std::string text);
	void SortDocsByDescLen();
};
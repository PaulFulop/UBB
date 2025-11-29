#pragma once
#include "Bill.h"
#include <vector>
#include <fstream>
#include <sstream>

class Repository {
public:
	Repository(std::string fileName);
	Repository();

	std::vector<Bill> bills;
	void ReadFromFile(std::string fileName);
	void SortBills();
	double TotalUnpaidBills(std::string companyName);
};
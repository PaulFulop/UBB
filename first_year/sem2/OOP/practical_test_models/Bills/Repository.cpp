#include "Repository.h"

Repository::Repository(std::string fileName) {
	ReadFromFile(fileName);
	SortBills();
}

Repository::Repository(): bills(std::vector<Bill>()){}

void Repository::ReadFromFile(std::string fileName){
	std::ifstream fin(fileName);
	std::string _companyName, _serialNumber, _sum, _isPaid;
	std::string line;

	while (std::getline(fin, line)) {
		std::stringstream ss(line);

		std::getline(ss, _companyName, ';');
		std::getline(ss, _serialNumber, ';');
		std::getline(ss, _sum, ';');
		std::getline(ss, _isPaid);

		bills.push_back(Bill(_companyName, _serialNumber, std::atof(_sum.c_str()), _isPaid == " true" ? true : false));
	}

	fin.close();
}

void Repository::SortBills() {
	for (int i = 0; i < bills.size() - 1; ++i)
		for (int j = i + 1; j < bills.size(); ++j)
			if (bills[i].companyName > bills[j].companyName)
				std::swap(bills[i], bills[j]);
}

double Repository::TotalUnpaidBills(std::string companyName) {
	double total = 0;
	for (const auto& bill : bills)
		if (!bill.isPaid && bill.companyName == companyName)
			total += bill.sum;

	return !total ? -1 : total;
}
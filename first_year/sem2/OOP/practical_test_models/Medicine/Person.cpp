#include "Person.h"
#include <fstream>

void Person::addAnalysis(MedicalAnalysis* a)
{
	analyses.push_back(a);
}

std::vector<MedicalAnalysis*> Person::getAllAnalyses()
{
	return analyses;
}

std::vector<MedicalAnalysis*> Person::getAnalysesByMonth(int month)
{
	std::vector<MedicalAnalysis*> result;

	for (const auto& analysis : analyses)
	{
		int m = std::stoi(analysis->getDate().substr(5, 2));
		if (m == month)
			result.push_back(analysis);
	}

	return result;
}

bool Person::IsIll(int month)
{
	std::vector<MedicalAnalysis*> a = getAnalysesByMonth(month);

	for (const auto& analysis : a)
		if (analysis->isResultOk())
			return false;
	
	return true;
}

std::vector<MedicalAnalysis*> Person::getAnalysesBetweenDates(std::string date1, std::string date2)
{
	std::vector<MedicalAnalysis*> result;
	int year1 = std::stoi(date1.substr(0, 4));
	int month1 = std::stoi(date1.substr(5, 2));
	int day1 = std::stoi(date1.substr(8, 2));

	int year2 = std::stoi(date2.substr(0, 4));
	int month2 = std::stoi(date2.substr(5, 2));
	int day2 = std::stoi(date2.substr(8, 2));


	for (const auto& analysis : analyses)
	{
		int year = std::stoi(analysis->getDate().substr(0, 4));
		int month = std::stoi(analysis->getDate().substr(5, 2));
		int day = std::stoi(analysis->getDate().substr(8, 2));

		if (year1 <= year && year <= year2 ||
			(year1 == year2 && month1 <= month && month <= month2) ||
			(year1 == year2 && month1 == month2 && day1 <= day && day <= day2))
			result.push_back(analysis);
	}

	return result;
}

void Person::writeToFile(std::string filename, std::string date1, std::string date2)
{
	std::ofstream fout(filename);
	std::vector<MedicalAnalysis*> a = getAnalysesBetweenDates(date1, date2);

	for (const auto& analysis : a)
		fout << analysis->toString() << '\n';
	
	fout.close();
}
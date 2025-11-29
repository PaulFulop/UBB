#pragma once
#include <string>
#include "MedicalAnalysis.h"
#include <vector>

class Person {
private:
	std::string name;
	std::vector<MedicalAnalysis*> analyses;
public:
	void addAnalysis(MedicalAnalysis* a);
	std::vector<MedicalAnalysis*> getAllAnalyses();
	std::vector<MedicalAnalysis*> getAnalysesByMonth(int month);
	bool IsIll(int month);
	std::vector<MedicalAnalysis*> getAnalysesBetweenDates(std::string date1, std::string date2);
	void writeToFile(std::string filename, std::string date1, std::string date2);
};
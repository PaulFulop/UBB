#pragma once
#include "Appliance.h"
#include <vector>

class Service {
private:
	std::vector<Appliance*> appliances;
public:
	void AddAppliance(Appliance* new_appliance);
	std::vector<Appliance*> GetAllAppliances();
	std::vector<Appliance*> GetInefficientAppliances();
	std::vector<Appliance*> GetAppliancesLessThanValue(double value);
	void SortAppliances(std::vector<Appliance*> appliances);
	void WriteToFile(std::string fileName, std::vector<Appliance*> appliances);
};
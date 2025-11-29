#include "Service.h"
#include <algorithm>
#include <fstream>

void Service::AddAppliance(Appliance* new_appliance)
{
	appliances.push_back(new_appliance);
}

std::vector<Appliance*> Service::GetAllAppliances()
{
	return appliances;
}

std::vector<Appliance*> Service::GetInefficientAppliances()
{
	std::vector<Appliance*> result;
	for (const auto& appliance : appliances)
		if (appliance->consumedElectricity() > 100)
			result.push_back(appliance);

	return result;
}

std::vector<Appliance*> Service::GetAppliancesLessThanValue(double value)
{
	std::vector<Appliance*> result;
	for (const auto& appliance : appliances)
		if (appliance->consumedElectricity() < value)
			result.push_back(appliance);

	return result;
}

void Service::SortAppliances(std::vector<Appliance*> appliances)
{
	int n = appliances.size();
	for (int i = 0; i < n - 1; ++i)
		for (int j = i + 1; j < n; ++j)
			if (appliances[i]->GetId() > appliances[j]->GetId())
				std::swap(appliances[i], appliances[j]);
}

void Service::WriteToFile(std::string fileName, std::vector<Appliance*> appliances)
{
	std::ofstream fout(fileName);

	for (const auto& appliance : appliances)
		fout << appliance->toString() << '\n';

	fout.close();
}
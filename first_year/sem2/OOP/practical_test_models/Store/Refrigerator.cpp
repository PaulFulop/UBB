#include "Refrigerator.h"

Refrigerator::Refrigerator() : Appliance(), elecUsageClass(""), hasFreezer(0) {}
Refrigerator::Refrigerator(std::string _id, std::string _elecUsageClass, bool _hasFreezer) : Appliance(_id), elecUsageClass(_elecUsageClass), hasFreezer(_hasFreezer) {}

double Refrigerator::consumedElectricity()
{
	double total = 0;
	if (elecUsageClass == "A++")
		total += 90;
	else
		total += 60;

	if (hasFreezer)
		total += 20;

	return total;
}

std::string Refrigerator::toString()
{
	return "Refrigerator: " + id + ", " + elecUsageClass + ", " + (hasFreezer == true ? "has freezer." : "does not have freezer.");
}
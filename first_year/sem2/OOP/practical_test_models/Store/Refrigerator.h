#pragma once
#include "Appliance.h"

class Refrigerator : public Appliance {
private:
	std::string elecUsageClass;
	bool hasFreezer;
public:
	Refrigerator();
	Refrigerator(std::string _id, std::string _elecUsageClass, bool _hasFreezer);
	double consumedElectricity() override;
	std::string toString() override;
};
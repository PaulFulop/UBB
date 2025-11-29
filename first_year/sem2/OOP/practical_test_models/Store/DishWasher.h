#pragma once
#include "Appliance.h"

class DishWasher : public Appliance {
private:
	double quantityPerHour;

public:
	DishWasher();
	DishWasher(std::string _id, double _quantityPerHour);
	double consumedElectricity() override;
	std::string toString() override;
};
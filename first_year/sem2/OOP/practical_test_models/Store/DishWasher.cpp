#include "DishWasher.h"

DishWasher::DishWasher() : quantityPerHour(0) {}
DishWasher::DishWasher(std::string _id, double _quantityPerHour) : Appliance(_id), quantityPerHour(_quantityPerHour) {}

double DishWasher::consumedElectricity()
{
	return quantityPerHour * 20;
}

std::string DishWasher::toString()
{
	return "Dish Washer: " + id + ", quantity consumed per hour: " + std::to_string(quantityPerHour) + ".";
}
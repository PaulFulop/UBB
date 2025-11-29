#include "Car.h"

double Car::computePrice()
{
	return engine->getPrice() + (numberOfDoors == 2 ? 7000 : 8500);
}

std::string Car::toString()
{
	return "Car with " + std::to_string(numberOfDoors) + " doors, price " + std::to_string(computePrice()) + " and " + engine->toString();
}
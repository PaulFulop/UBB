#include "ElectricEngine.h"

double ElectricEngine::getPrice()
{
	return basePrice + basePrice + (autonomy * 0.01);
}

std::string ElectricEngine::toString()
{
	return "electic engine with autonomy " + std::to_string(autonomy) + " and engine price " + std::to_string(getPrice());
}
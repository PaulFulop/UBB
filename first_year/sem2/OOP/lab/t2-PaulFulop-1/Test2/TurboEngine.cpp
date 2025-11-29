#include "TurboEngine.h"

double TurboEngine::getPrice()
{
	return basePrice + basePrice + 100;
}

std::string TurboEngine::toString()
{
	return "turbo engine with engine price " + std::to_string(getPrice());;
}
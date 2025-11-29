#include "BP.h"

bool BP::isResultOk()
{
	return syastolicValue >= 90 && syastolicValue <= 119 && diastolicValue >= 60 && diastolicValue <= 79;
}

std::string BP::toString()
{
	return date + ", " + std::to_string(syastolicValue) + ", " + std::to_string(diastolicValue);
}

void BP::setSyastolicValue(int s)
{
	syastolicValue = s;
}

void BP::setDiastolicValue(int d)
{
	diastolicValue = d;
}
#include "BMI.h"

bool BMI::isResultOk()
{
	return value >= 19 && value <= 25;
}

void BMI::setValue(int v)
{
	value = v;
}

std::string BMI::toString()
{
	return date + ", " + std::to_string(value);
}
#pragma once
#include "Engine.h"

class ElectricEngine : public Engine {
private:
	int autonomy;
public:
	ElectricEngine(): autonomy (0) {}
	ElectricEngine(int _autonomy): autonomy (_autonomy) {}
	double getPrice() override;
	std::string toString() override;
};
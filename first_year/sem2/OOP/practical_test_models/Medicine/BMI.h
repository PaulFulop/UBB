#pragma once
#include "MedicalAnalysis.h"

class BMI : public MedicalAnalysis {
private:
	int value;
public:
	bool isResultOk() override;
	void setValue(int v);
	std::string toString() override;
};
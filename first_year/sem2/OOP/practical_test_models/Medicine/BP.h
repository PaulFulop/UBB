#pragma once
#include "MedicalAnalysis.h"

class BP : public MedicalAnalysis {
private:
	int syastolicValue, diastolicValue;
public:
	void setSyastolicValue(int s);
	void setDiastolicValue(int d);
	bool isResultOk() override;
	std::string toString() override;
};
#pragma once
#include <string>

class MedicalAnalysis {
protected:
	std::string date;
public:
	virtual bool isResultOk() = 0;
	virtual std::string getDate() { return date; }
	virtual void setDate(std::string new_date) { date = new_date; }
	virtual std::string toString() = 0;
};

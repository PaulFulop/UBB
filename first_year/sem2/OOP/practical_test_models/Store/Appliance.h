#pragma once
#include <string>

class Appliance {
protected:
	std::string id;
public:
	Appliance(): id ("") {}
	Appliance(std::string _id): id (_id) {}
	virtual std::string GetId() { return id; }
	virtual double consumedElectricity() = 0;
	virtual std::string toString() = 0;
};
#pragma once
#include <string>

class Engine {
protected:
	double basePrice = 3000;
public:
	//Engine(): basePrice (0) {}
	//Engine(double _basePrice): basePrice(_basePrice) {}
	virtual double getPrice() = 0;
	virtual std::string toString() = 0;
};
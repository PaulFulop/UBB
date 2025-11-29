#pragma once
#include "Engine.h"

class Car {
private:
	int numberOfDoors;
	Engine* engine;
public:
	Car() : numberOfDoors(0), engine(nullptr) {}
	Car(int _numberOfDoors, Engine* _engine): numberOfDoors(_numberOfDoors), engine(_engine) {}
	double computePrice();
	std::string toString();
};
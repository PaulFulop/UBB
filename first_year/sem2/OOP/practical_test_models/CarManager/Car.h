#pragma once
#include <string>
using namespace std;

class Car {
public:
	string name, model, color;
	int year;

	Car();
	Car(string _name, string _model, int _year, string _color);

	string ToString() const;
	bool ValidCar() const;
};
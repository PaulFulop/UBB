#include "Car.h"

Car::Car() : name{ "" }, model{ "" }, year{ 0 }, color{ "" }
{}

Car::Car(string _name, string _model, int _year, string _color): name{ _name }, model{ _model }, year{ _year }, color{ _color }
{}

string Car::ToString() const
{
	return name + ", " + model + ", " + to_string(year) + ", " + color + ".";
}

bool Car::ValidCar() const
{
	if (year < 0 || year < 1000) return false;
	return true;
}
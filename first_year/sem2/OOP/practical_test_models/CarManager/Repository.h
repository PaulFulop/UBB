#pragma once
#include <vector>
#include "Car.h"

class Repository {
public:
	vector<Car> cars;

	Repository();

	bool AddCar(Car newCar);
	bool RemoveCar(Car car);
	int SearchCar(Car car);
	Repository FilterCars(int year) const;
};
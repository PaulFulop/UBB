#pragma once
#include <vector>
#include "Car.h"
#include <string>

class Service {
private:
	std::vector<Car> cars;
public:
	void addCar(int numberOfDoors, std::string engineType, int autonomy);
	std::vector<Car> getAllCars();
	std::vector<Car> getCarsWithMaxPrice(double maxPrice);
	void writeToFile(std::string fileName, std::vector<Car> c);
};
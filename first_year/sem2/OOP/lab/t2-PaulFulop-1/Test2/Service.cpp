#include "Service.h"
#include "ElectricEngine.h"
#include "TurboEngine.h"
#include <fstream>

void Service::addCar(int numberOfDoors, std::string engineType, int autonomy)
{
	if (engineType == "Electric")
		cars.push_back(Car(numberOfDoors, new ElectricEngine(autonomy)));
	else
		cars.push_back(Car(numberOfDoors, new TurboEngine));
}

std::vector<Car> Service::getAllCars()
{
	return cars;
}

std::vector<Car> Service::getCarsWithMaxPrice(double maxPrice)
{
	std::vector<Car> c;

	for (auto& car : cars)
		if (car.computePrice() < maxPrice)
			c.push_back(car);

	return c;
}

void Service::writeToFile(std::string fileName, std::vector<Car> c)
{
	std::ofstream fout(fileName);

	for (auto& car : c)
		fout << car.toString() << '\n';
}
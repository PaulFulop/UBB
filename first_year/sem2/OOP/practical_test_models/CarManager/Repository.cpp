#include "Repository.h"

Repository::Repository(): cars {vector<Car>()}
{}

bool Repository::AddCar(Car newCar)
{
	if (SearchCar(newCar) != -1)
		return false;

	cars.push_back(newCar);
	return true;
}

bool Repository::RemoveCar(Car car)
{
	int pos = SearchCar(car);
	if (pos == -1)
		return false;

	cars.erase(cars.begin() + pos);
	return true;
}

int Repository::SearchCar(Car car)
{
	for (int i = 0; i < cars.size(); ++i)
		if (cars[i].model == car.model && cars[i].year == car.year)
			return i;

	return -1;
}

Repository Repository::FilterCars(int year) const
{
	Repository filtCars = Repository();
	for (int i = 0; i < cars.size(); ++i)
		if (2025 - cars[i].year > year)
			filtCars.AddCar(cars[i]);

	return filtCars;
}
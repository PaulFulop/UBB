#include "Service.h"
#include <exception>

Service::Service(): repo {Repository()}
{}

void Service::AddCar(Car newCar)
{
	if (!repo.AddCar(newCar))
		throw exception("Duplicate car.\n");
}

void Service::RemoveCar(Car car)
{
	if (!repo.RemoveCar(car))
		throw exception("Inexistent car.\n");
}

void Service::SortCarsByManufacturerModel(Repository& repo) const
{
	for (int i = 0; i < repo.cars.size() - 1; ++i)
		for (int j = i + 1; j < repo.cars.size(); ++j)
			if (repo.cars[i].name > repo.cars[j].name ||
				(repo.cars[i].name == repo.cars[j].name && repo.cars[i].model > repo.cars[j].model))
				swap(repo.cars[i], repo.cars[j]);
}

void Service::SortCarsByColor(Repository& repo) const
{
	for (int i = 0; i < repo.cars.size() - 1; ++i)
		for (int j = i + 1; j < repo.cars.size(); ++j)
			if (repo.cars[i].color > repo.cars[j].color)
				swap(repo.cars[i], repo.cars[j]);
}

Repository Service::FilterVintageCars() const
{
	return repo.FilterCars(45);
}

string Service::ListCars(Repository repo) const
{
	string s = "\n";

	for (int i = 0; i < repo.cars.size(); ++i)
		s += repo.cars[i].ToString() + "\n";

	return s;
}

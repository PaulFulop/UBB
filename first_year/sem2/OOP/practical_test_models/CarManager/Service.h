#pragma once
#include "Repository.h"

class Service {
public:
	Repository repo;

	Service();

 /**
     @brief Adds a new car to the repository.
     @param newCar - The new car to add.
 **/
	void AddCar(Car newCar);
	void RemoveCar(Car car);
	void SortCarsByManufacturerModel(Repository& repo) const;

 /**
     @brief  Sorts cars by color
     @param repo - the repository for which to sort them
 **/
	void SortCarsByColor(Repository& repo) const; 

 /**
     @brief  Filters al the vintage cars from the servce and puts them in a repo
     @retval  - The repository of the filtered cars
 **/
	Repository FilterVintageCars() const;
	string ListCars(Repository repo) const;
};
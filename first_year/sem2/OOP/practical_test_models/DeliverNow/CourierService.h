#pragma once
#include "Repository.h"
#include "Package.h"
#include "Courier.h"

class CourierService {
public:
	Repository<Package>* packages = nullptr;
	Courier* c = nullptr;
	std::vector<Package> courierPackages;

	CourierService(Repository<Package>* packages, Courier* c);
	void FilterCourierPackages();
	bool IsAssignedStreet(std::string street);

	CourierService(): packages(nullptr), c(nullptr), courierPackages(std::vector<Package>()){}
};
#pragma once
#include "Department.h"
#include "Volunteer.h"
#include "Repository.h"
#include <vector>

class Service{
public:
	Department* d;
	Repository<Volunteer>* volunteers;

	Service() = default;

	Service(Department* d, Repository<Volunteer>* volunteers)
		: d(d), volunteers(volunteers)
	{
	}

	std::vector<Volunteer> UnassignedVolunteers();
	std::vector<Volunteer> VolunteersOfDepartment();
	std::vector<Volunteer> Top3();
	void AddVolunteer(const Volunteer& newVolunteer);
	int NrOfVolunteers();
};
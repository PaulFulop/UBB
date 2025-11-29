#include "Service.h"
#include <algorithm>

std::vector<Volunteer> Service::UnassignedVolunteers() {
	std::vector<Volunteer> uV;

	for (const auto& v : volunteers->data)
		if (v.department.desc == "" && v.department.name == "")
			uV.push_back(v);

	return uV;
}

std::vector<Volunteer> Service::VolunteersOfDepartment() {
	std::vector<Volunteer> vOD;

	for (const auto& v : volunteers->data)
		if (v.department.desc == d->desc && v.department.name == d->name)
			vOD.push_back(v);

	if (vOD.empty()) return vOD;
	for (int i = 0; i < vOD.size() - 1; ++i)
		for (int j = i + 1; j < vOD.size(); ++j)
			if (vOD[i].name > vOD[j].name)
				std::swap(vOD[i], vOD[j]);

	return vOD;
}

std::vector<Volunteer> Service::Top3() {
	std::vector<Volunteer> uV = UnassignedVolunteers();

	for (int i = 0; i < uV.size() - 1; ++i)
		for (int j = i + 1; j < uV.size(); ++j)
			if (uV[i].SuitabilityScore() > uV[j].SuitabilityScore())
				std::swap(uV[i], uV[j]);

	std::vector<Volunteer> top3;
	top3.push_back(uV[0]);
	top3.push_back(uV[1]);
	top3.push_back(uV[2]);
	return top3;
}

void Service::AddVolunteer(const Volunteer& newVolunteer) {
	if (newVolunteer.name == "" || newVolunteer.email == "")
		throw std::exception("Invalid volunteer!");

	volunteers->Add(newVolunteer);
}

int Service::NrOfVolunteers() {
	return VolunteersOfDepartment().size();
}
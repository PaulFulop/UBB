#include "Service.h"
#include <algorithm>

std::vector<Patient> Service::PatientsOfSameNeededSpecialiation() {
	std::vector<Patient> patientsOfSameNeededSpecialiation;
	for (const auto& p : patients->data)
		if (ValidPatient(p)) patientsOfSameNeededSpecialiation.push_back(p);

	return patientsOfSameNeededSpecialiation;
}

std::vector<Patient> Service::PatientsOfDoctor() {
	std::vector<Patient> patientsOfDoctor;
	for (const auto& p : patients->data)
		if (PatientTreatedByDoctor(p)) patientsOfDoctor.push_back(p);

	return patientsOfDoctor;
}

void Service::SortPatients(std::vector<Patient>& _patients) {
	std::sort(_patients.begin(), _patients.end(), [](const Patient& p1, const Patient& p2) {return p1.admissionDate < p2.admissionDate; });
}

bool Service::PatientTreatedByDoctor(const Patient& p) const {
	return p.doctor == d.name;
}

void Service::AddPatient(std::string name, std::string diagnosis, std::string specialisation, std::string doctor, std::string date) {
	if (name == "") throw std::exception("The name of the patient is empty!");
	if (diagnosis == "") diagnosis = "undiagnosed";
	patients->Add(Patient(name, diagnosis, specialisation, doctor, date));
}

bool Service::ValidPatient(const Patient& p) const {
	return p.diagnosis == "undiagnosed" || p.specialisation == d.specialisation;
}

bool Service::ModifiablePatientData(const Patient& p) const {
	return p.diagnosis == "undiagnosed" || p.doctor == d.name;
}

void Service::UpdatePatientData(Patient& p, std::string newDiagnosis, std::string newSpecialisation) {
	if (newDiagnosis == "undiagnosed" || newDiagnosis == "") throw std::exception("Invalid diagnosis!");
	p.diagnosis = newDiagnosis;
	p.specialisation = newSpecialisation;
}
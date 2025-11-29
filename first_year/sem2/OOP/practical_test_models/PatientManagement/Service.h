#pragma once
#include "Doctor.h"
#include "Patient.h"
#include "Repo.h"

class Service{
public:
	Doctor d;
	Repo<Patient>* patients;


	Service() = default;
	Service(const Doctor& d, Repo<Patient>* patients)
		: d(d), patients(patients)
	{}

	std::vector<Patient> PatientsOfSameNeededSpecialiation();
	std::vector<Patient> PatientsOfDoctor();
	void SortPatients(std::vector<Patient>& _patients);
	bool PatientTreatedByDoctor(const Patient& p) const;
	void AddPatient(std::string name, std::string diagnosis, std::string specialisation, std::string doctor, std::string date);
	bool ValidPatient(const Patient& p) const;
	void UpdatePatientData(Patient& p, std::string newDiagnosis, std::string newSpecialisation);
	bool ModifiablePatientData(const Patient& p) const;
};
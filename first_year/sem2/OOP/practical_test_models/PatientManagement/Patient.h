#pragma once
#include <string>

class Patient{
public:
	std::string name, diagnosis, specialisation, doctor, admissionDate;

	Patient() = default;

	Patient(const std::string& name, const std::string& diagnosis, const std::string& specialisation, const std::string& doctor, const std::string& admissionDate)
		: name(name), diagnosis(diagnosis), specialisation(specialisation), doctor(doctor), admissionDate(admissionDate)
	{}

	friend std::istream& operator >> (std::istream& is, Patient& p);
	friend std::ostream& operator << (std::ostream& os, const Patient& p);
	std::string ToString() const;
};


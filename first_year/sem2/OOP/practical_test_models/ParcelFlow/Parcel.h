#pragma once
#include <string>
#include <vector>

class Parcel {
public:
	std::string name, adrStreet;
	int adrNumber;
	double locationX, locationY;
	bool delivered;

	Parcel(std::string _name, std::string _adrStreet, int _adrNumber, double _locationX, double _locationY, bool _delivered):
		name (_name), adrStreet (_adrStreet), adrNumber(_adrNumber), locationX(_locationX), locationY(_locationY), delivered(_delivered) { }

	std::string ToString() const;
	friend std::istream& operator >> (std::istream& is, Parcel& parcel);
	friend std::ostream& operator << (std::ostream& os, const Parcel& parcel);

	Parcel() = default;
};
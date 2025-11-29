#include "Parcel.h"
#include "Utils.h"

std::string Parcel::ToString() const {
	return name + "," + adrStreet + " Nr. " + std::to_string(adrNumber) + "," + std::to_string(locationX) + " " + std::to_string(locationY) +
		"," + (delivered == true ? "delivered" : "not delivered");
}

std::istream& operator >> (std::istream& is, Parcel& parcel) {
	std::string line;
	std::getline(is, line);

	std::vector<std::string> tokens = Tokenize(line, ';');
	if (tokens.size() != 6) return is;

	parcel = Parcel(tokens[0], tokens[1], std::atoi(tokens[2].c_str()), std::atof(tokens[3].c_str()), std::atof(tokens[4].c_str()), (tokens[5] == "false" ? false : true));
	return is;
}

std::ostream& operator << (std::ostream& os, const Parcel& parcel) {
	os << parcel.name + ";" + parcel.adrStreet + ";" + std::to_string(parcel.adrNumber) + ";" + std::to_string(parcel.locationX) + ";" +
		std::to_string(parcel.locationY) + ";" + (parcel.delivered == true ? "true" : "false");
	return os;
}

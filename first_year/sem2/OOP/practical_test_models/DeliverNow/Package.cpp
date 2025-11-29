#include "Package.h"
#include "Utils.h"

std::istream& operator >> (std::istream& is, Package& p) {
	std::string line;
	std::getline(is, line);
	std::vector<std::string> tokens = Tokenize(line, ',');
	if (tokens.size() != 6)
		return is;

	std::string recipient = tokens[0];
	std::string addressStreet = tokens[1];
	int addressNumber = std::atoi(tokens[2].c_str());
	double x = std::atof(tokens[3].c_str());
	double y = std::atof(tokens[4].c_str());
	bool deliveryStatus = tokens[5] == "false" ? false : true;
	p = Package(recipient, addressStreet, addressNumber, x, y, deliveryStatus);

	return is;
}

std::string Package::ToString() const {
	return recipient + ", " + addressStreet + " " + std::to_string(addressNumber) + ", " + std::to_string(x)
		+ " " + std::to_string(y) + ", " + (deliveryStatus == false ? "false" : "true");
}

std::ostream& operator << (std::ostream& os, const Package& p) {
	os << p.recipient << ',' << p.addressStreet << ',' << p.addressNumber << ',' << p.x << ',' << p.y << ',' << (!p.deliveryStatus ? "false" : "true");
	return os;
}
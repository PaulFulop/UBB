#pragma once
#include <string>

class Package {
public:
	std::string recipient, addressStreet;
	int addressNumber;
	double x, y;
	bool deliveryStatus;



	Package() = default;
	Package(const std::string& recipient, const std::string& addressStreet, int addressNumber, double x, double y, bool deliveryStatus)
		: recipient(recipient), addressStreet(addressStreet), addressNumber(addressNumber), x(x), y(y), deliveryStatus(deliveryStatus)
	{}

	friend std::istream& operator >> (std::istream& is, Package& p);
	friend std::ostream& operator << (std::ostream& os, const Package& p);
	std::string ToString() const;
};
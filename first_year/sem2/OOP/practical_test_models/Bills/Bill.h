#pragma once
#include <string>

class Bill {
public:
	std::string companyName, serialNumber;
	double sum;
	bool isPaid;

	Bill(std::string _companyName, std::string _serialNumber, double _sum, bool _isPaid);
	std::string ToString();
};
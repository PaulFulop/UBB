#include "Bill.h"

Bill::Bill(std::string _companyName, std::string _serialNumber, double _sum, bool _isPaid): companyName (_companyName),
serialNumber (_serialNumber), sum (_sum), isPaid (_isPaid) {}

std::string Bill::ToString() {
	return companyName + " " + std::to_string(sum);
}
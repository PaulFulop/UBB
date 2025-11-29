#include "CourierService.h"

CourierService::CourierService(Repository<Package>* packages, Courier* c)
	: packages(packages), c(c){
	FilterCourierPackages();
}

void CourierService::FilterCourierPackages() {
	courierPackages.clear();

	for (const auto& p : packages->data) {
		if (!p.deliveryStatus && IsAssignedStreet(p.addressStreet))
			courierPackages.push_back(p);
	}
}

bool CourierService::IsAssignedStreet(std::string street) {
	for (const auto& str : c->streets)
		if (str == street)
			return true;
	return false;
}
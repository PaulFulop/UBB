#include "User.h"
#include <iostream>

std::istream& operator >> (std::istream& is, User& u) {
	is >> u.name;
	return is;
}

std::ostream& operator << (std::ostream& os, const User& u) {
	os << u.name;
	return os;
}
#include "Ticket.h"

std::istream& operator >> (std::istream& is, Ticket& t) {
	is >> t.personPos >> t.eventPos;
	return is;
}

std::ostream& operator << (std::ostream& os, const Ticket& t) {
	os << t.personPos << ' ' << t.eventPos;
	return os;
}
#pragma once
#include <iostream>

class Ticket{
public:
	int personPos, eventPos;

	friend std::istream& operator >> (std::istream& is, Ticket& t);
	friend std::ostream& operator << (std::ostream& os, const Ticket& p);

	Ticket() = default;

	Ticket(int personPos, int eventPos)
		: personPos(personPos), eventPos(eventPos)
	{
	}

	bool operator == (const Ticket& other) {
		return personPos == other.personPos && eventPos == other.eventPos;
	}
};


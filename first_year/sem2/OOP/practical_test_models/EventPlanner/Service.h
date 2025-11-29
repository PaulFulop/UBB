#pragma once
#include "Repo.h"
#include "Person.h"
#include "Event.h"
#include "Ticket.h"

class Service{
public:
	Person person;
	Repo<Event>* events;
	Repo<Person>* persons;
	Repo<Ticket>* tickets;
	int personPos = -1;

	Service() = default;
	Service(Person& person, Repo<Event>* events, Repo<Person>* _persons, Repo<Ticket>* _tickets)
		: person(person), events(events), persons(_persons), tickets(_tickets)
	{
		personPos = GetPersonPosition(person);
	}

	std::string PersonLocationStr() const;
	std::vector<Event> SortedEvents() const;
	void AddEvent(const Event& newEvent);
	void AttendEvent(Event& e);
	std::vector<Person> PersonsGoingToEvent(Event& e);
	int GetPersonPosition(Person& p);
	int GetEventPosition(Event& e);
	std::vector<Event> NearEvents();
	bool IsPersonGoingToEvent(Person& p, Event& e);
	bool IsEventOrganisedByOrganiser(const Event& e) const;
};
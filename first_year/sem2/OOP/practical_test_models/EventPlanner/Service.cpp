#include "Service.h"
#include <algorithm>

std::string Service::PersonLocationStr() const {
	return std::to_string(person.latitude) + " " + std::to_string(person.longitude);
}

std::vector<Event> Service::SortedEvents() const {
	std::vector<Event> sEvents = events->data;
	std::sort(sEvents.begin(), sEvents.end(), [](const Event& e1, const Event& e2) {return e1.date < e2.date; });
	return sEvents;
}

void Service::AddEvent(const Event& newEvent) {
	for (auto& event : events->data)
		if (event == newEvent)
			throw std::exception("Duplicate event!");

	events->Add(newEvent);
}

void Service::AttendEvent(Event& e) {
	int eventPos = GetEventPosition(e);
	Ticket newTicket = Ticket(personPos, eventPos);
	tickets->Add(newTicket);
}

std::vector<Person> Service::PersonsGoingToEvent(Event& e) {
	std::vector<Person> personsGoing;
	int eventPos = GetEventPosition(e);
	for (int i = 0; i < persons->data.size(); ++i)
		for (const auto& ticket : tickets->data)
			if (ticket.personPos == i && ticket.eventPos == eventPos)
				personsGoing.push_back(persons->data[i]);

	return personsGoing;
}

int Service::GetPersonPosition(Person& p) {
	int i;
	for (i = 0; i < persons->data.size(); ++i)
		if (p == persons->data[i]) return i;
	return i;
}

int Service::GetEventPosition(Event& e) {
	int i;
	for (i = 0; i < events->data.size(); ++i)
		if (e == events->data[i]) return i;
	return i;
}

std::vector<Event> Service::NearEvents() {
	std::vector<Event> nearEvents;
	for (const auto& e : events->data)
		if (person.NearEvent(e.latitude, e.longitude))
			nearEvents.push_back(e);

	return nearEvents;
}

bool Service::IsPersonGoingToEvent(Person& p, Event& e) {
	int personPos = GetPersonPosition(p);
	int eventPos = GetEventPosition(e);

	for (const auto& ticket : tickets->data)
		if (ticket.eventPos == eventPos && ticket.personPos == personPos) return true;
	return false;
}

bool Service::IsEventOrganisedByOrganiser(const Event& e) const {
	return person.IsOrganiser() && person.name == e.organiser;
}
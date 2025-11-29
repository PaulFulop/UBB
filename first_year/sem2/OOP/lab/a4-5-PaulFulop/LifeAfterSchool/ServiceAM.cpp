#include "ServiceAM.h"
#include <exception>

ServiceAM::ServiceAM(): repo {Repository()}
{}

void ServiceAM::AddEvent(Event new_event)
{
	if (!repo.AddToRepo(new_event))
		throw exception("The event already exists (duplicate title).\n");
}

void ServiceAM::RemoveEvent(string title)
{
	Event event = Event();
	event.title = title;
	if (!repo.RemoveFromRepo(event))
		throw exception("Event not found.\n");
}

void ServiceAM::UpdateEvent(Event event, Event new_event)
{
	if (!repo.UpdateToRepo(event, new_event))
		throw exception("Event not found.\n");
}

string ServiceAM::ListFilterEvents(int participants_filter) const
{
	DynamicVector<Event> filteredEvents = repo.FilterEvents(participants_filter);

	string listOfFilteredEvents = "\n";

	for (int i = 0; i < filteredEvents.length; ++i)
		listOfFilteredEvents += filteredEvents.data[i].ToString() + '\n';

	return listOfFilteredEvents;
}

string ServiceAM::ListOfEvents() const
{
	string listOfEvents = "\n";

	for (int i = 0; i < repo.events.length; ++i)
		listOfEvents += repo.events.data[i].ToString() + '\n';

	return listOfEvents;
}
#include "Repository.h"

Repository::Repository(): events {DynamicVector<Event>()}
{}

Repository::Repository(const Repository& other)
{
	events = other.events;
}

bool Repository::AddToRepo(Event new_event)
{
	return events.Add(new_event);
}

bool Repository::RemoveFromRepo(Event event)
{
	return events.Remove(event);
}

bool Repository::UpdateToRepo(Event event, Event new_event)
{
	return events.Update(event, new_event);
}

DynamicVector<Event> Repository::FilterEvents(int participants_filter) const
{
	DynamicVector<Event> filteredEvents = DynamicVector<Event>();

	for (int i = 0; i < events.length; ++i)
		if (events.data[i].nr_of_people < participants_filter)
			filteredEvents.Add(events.data[i]);

	return filteredEvents;
}

Repository& Repository::operator=(const Repository& other)
{
	events = other.events;
	return *this;
}
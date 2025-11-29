#include "MemoryRepository.h"
#include <algorithm>

MemoryRepository::MemoryRepository(): Repository(events)
{}

MemoryRepository::MemoryRepository(const MemoryRepository& other)
{
	events = other.events;
}

void MemoryRepository::AddToRepo(Event new_event)
{
	if (find(events.begin(), events.end(), new_event) != events.end())
		throw DuplicateEventException();

	events.push_back(new_event);
}

void MemoryRepository::RemoveFromRepo(Event event)
{
	const auto& it = find(events.begin(), events.end(), event);
	if (it == events.end())
		throw InexistentEventException();
	
	events.erase(it);
}

void MemoryRepository::UpdateToRepo(Event event, Event new_event)
{
	auto it = find(events.begin(), events.end(), event);
	if (it == events.end())
		throw InexistentEventException();

	EventValidator::Validate(new_event);
	
	*it = new_event;
}

std::vector<Event> MemoryRepository::GetEvents()
{
	return events;
}

std::vector<Event> MemoryRepository::FilterEvents(int participants_filter) const
{
	std::vector<Event> filteredEvents = std::vector<Event>(events.size());

	copy_if(events.begin(), events.end(), filteredEvents.begin(),
		[&participants_filter](Event event) {return event.nr_of_people < participants_filter; });

	filteredEvents.erase(remove_if(filteredEvents.begin(), filteredEvents.end(), [](Event event) {return event.title == ""; }), filteredEvents.end());
	return filteredEvents;
}

Repository* MemoryRepository::Clone() const
{
	return new MemoryRepository(*this);
}

MemoryRepository& MemoryRepository::operator=(const MemoryRepository& other)
{
	events = other.events;
	return *this;
}
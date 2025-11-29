#include "FileRepository.h"
#include <algorithm>
#include <fstream>

FileRepository::FileRepository() : Repository(events), fileDescriptor { "" }
{}

FileRepository::FileRepository(const FileRepository& other)
{
	events = other.events;
	fileDescriptor = other.fileDescriptor;
}

FileRepository::FileRepository(std::string _fileDescriptor) : fileDescriptor { _fileDescriptor }
{
	ReadFromFile();
}

void FileRepository::AddToRepo(Event new_event)
{
	if (find(events.begin(), events.end(), new_event) != events.end())
		throw DuplicateEventException();

	events.push_back(new_event);
	SaveToFile();
}

void FileRepository::FileRepository::RemoveFromRepo(Event event)
{
	const auto& it = find(events.begin(), events.end(), event);
	if (it == events.end())
		throw InexistentEventException();

	events.erase(it);
	SaveToFile();
}

void FileRepository::UpdateToRepo(Event event, Event new_event)
{
	auto it = find(events.begin(), events.end(), event);
	if (it == events.end())
		throw InexistentEventException();

	EventValidator::Validate(new_event);

	*it = new_event;
	SaveToFile();
}

void FileRepository::Refresh()
{
	SaveToFile();
}

std::vector<Event> FileRepository::GetEvents()
{
	return events;
}

std::vector<Event> FileRepository::FilterEvents(int participants_filter) const
{
	std::vector<Event> filteredEvents = std::vector<Event>(events.size());

	copy_if(events.begin(), events.end(), filteredEvents.begin(),
		[&participants_filter](Event event) {return event.nr_of_people < participants_filter; });

	filteredEvents.erase(remove_if(filteredEvents.begin(), filteredEvents.end(), [](Event event) {return event.title == ""; }), filteredEvents.end());
	return filteredEvents;
}

Repository* FileRepository::Clone() const
{
	return new FileRepository(*this);
}

FileRepository& FileRepository::operator=(const FileRepository& other)
{
	events = other.events;
	return *this;
}

void FileRepository::SaveToFile()
{
	std::ofstream fout(fileDescriptor);

	if (!fout.is_open())
		throw EventsFileException();
	
	for (const auto& event : events)
		fout << event << '\n';

	fout.close();
}

void FileRepository::ReadFromFile()
{
	events.clear();
	std::ifstream fin(fileDescriptor);

	if (!fin.is_open())
		throw EventsFileException();

	Event e;
	while (fin >> e)
		events.push_back(e);

	fin.close();
}
#include "ServiceUM.h"

ServiceUM::ServiceUM(Repository* _globalRepo): userRepo {Repository()}, globalRepo {_globalRepo}
{ }

ServiceUM::~ServiceUM()
{
	//delete[] globalRepo;
}

void ServiceUM::AddUserEvent(int pos)
{
	if (pos > globalRepo->events.length)
		throw exception("Out of range.\n");

	if (!userRepo.AddToRepo(globalRepo->events.data[pos]))
		throw exception("This event has already been added.\n");
	
	++globalRepo->events.data[pos].nr_of_people;
}

void ServiceUM::RemoveUserEvent(string title)
{
	Event userEvent = Event();
	userEvent.title = title;
	if (!userRepo.RemoveFromRepo(userEvent))
		throw exception("Event not found.\n");

	for (int i = 0; i < globalRepo->events.length; ++i)
		if (userEvent == globalRepo->events.data[i])
		{
			--globalRepo->events.data[i].nr_of_people;
			break;
		}
}

void ServiceUM::SortEventsByDate(Repository& repo) const
{
	int length = repo.events.length;
	for (int i = 0; i < length - 1; ++i)
		for (int j = i + 1; j < length; ++j)
		{
			int yearI = stoi(repo.events.data[i].dt.substr(repo.events.data[i].dt.find_last_of("/") + 1, 4));
			int yearJ = stoi(repo.events.data[j].dt.substr(repo.events.data[j].dt.find_last_of("/") + 1, 4));

			int monthI = stoi(repo.events.data[i].dt.substr(0, 2));
			int monthJ = stoi(repo.events.data[j].dt.substr(0, 2));

			int dayI = stoi(repo.events.data[i].dt.substr(repo.events.data[i].dt.find_first_of("/") + 1, 2));
			int dayJ = stoi(repo.events.data[j].dt.substr(repo.events.data[j].dt.find_first_of("/") + 1, 2));

			if (yearI > yearJ || (yearI == yearJ && monthI > monthJ) || (yearI == yearJ && monthI == monthJ && dayI > dayJ))
			{
				Event auxEvent = repo.events.data[j];
				repo.events.data[j] = repo.events.data[i];
				repo.events.data[i] = auxEvent;
			}
		}
}

Repository ServiceUM::GetEventsByMonth(int month) const
{
	Repository filteredEvents = Repository();

	for (int i = 0; i < globalRepo->events.length; ++i)
		if (stoi(globalRepo->events.data[i].dt.substr(0, 2)) == month)
			filteredEvents.AddToRepo(globalRepo->events.data[i]);

	return filteredEvents;
}

string ServiceUM::ListUserEvents() const
{
	string listOfEvents = "\n";

	for (int i = 0; i < userRepo.events.length; ++i)
		listOfEvents += userRepo.events.data[i].ToString() + '\n';

	return listOfEvents;
}
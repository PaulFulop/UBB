#include "ServiceUM.h"

ServiceUM::ServiceUM() : userRepo{ nullptr }, globalRepo{ nullptr }, eventViewer{ nullptr } {}

ServiceUM::ServiceUM(Repository* _userRepo, Repository* _globalRepo, EventViewer* _eventViewer) : userRepo{ _userRepo }, globalRepo{ _globalRepo }, eventViewer { _eventViewer }
{}

ServiceUM::~ServiceUM()
{
	if (eventViewer != nullptr)
		eventViewer->Clear();

	delete userRepo;
	delete eventViewer;
}

void ServiceUM::AddUserEvent(int pos)
{
	if (pos > globalRepo->events.size())
		throw OutOfRangeException();

	if (userRepo != nullptr && globalRepo != nullptr && eventViewer != nullptr)
	{
		userRepo->AddToRepo(globalRepo->events[pos]);
		++globalRepo->events[pos].nr_of_people;
		++userRepo->events[userRepo->events.size() - 1].nr_of_people;
		globalRepo->Refresh();
		userRepo->Refresh();
		eventViewer->StoreData();
	}
}

void ServiceUM::RemoveUserEvent(std::string title)
{
	if (userRepo != nullptr && globalRepo != nullptr && eventViewer != nullptr)
	{
		Event userEvent = Event();
		userEvent.title = title;
		userRepo->RemoveFromRepo(userEvent);

		auto it = find(globalRepo->events.begin(), globalRepo->events.end(), userEvent);
		if (it != globalRepo->events.end())
			--it->nr_of_people;

		globalRepo->Refresh();
		eventViewer->StoreData();
	}
}

void ServiceUM::SortEventsByDate(Repository* repo) const
{
	if (repo != nullptr)
	{
		size_t length = repo->events.size();
		for (int i = 0; i < length - 1; ++i)
			for (int j = i + 1; j < length; ++j)
			{
				int yearI = stoi(repo->events[i].dt.substr(repo->events[i].dt.find_last_of("/") + 1, 4));
				int yearJ = stoi(repo->events[j].dt.substr(repo->events[j].dt.find_last_of("/") + 1, 4));

				int monthI = stoi(repo->events[i].dt.substr(0, 2));
				int monthJ = stoi(repo->events[j].dt.substr(0, 2));

				int dayI = stoi(repo->events[i].dt.substr(repo->events[i].dt.find_first_of("/") + 1, 2));
				int dayJ = stoi(repo->events[j].dt.substr(repo->events[j].dt.find_first_of("/") + 1, 2));

				if (yearI > yearJ || (yearI == yearJ && monthI > monthJ) || (yearI == yearJ && monthI == monthJ && dayI > dayJ))
					std::swap(repo->events[i], repo->events[j]);
			}
	}
}

Repository* ServiceUM::GetEventsByMonth(int month) const
{
	if (globalRepo != nullptr)
	{
		Repository* filteredEvents = globalRepo->Clone();

		for (const auto& event : globalRepo->events)
			if (stoi(event.dt.substr(0, 2)) != month)
				filteredEvents->RemoveFromRepo(event);

		return filteredEvents;
	}

	return nullptr;
}

std::string ServiceUM::ListUserEvents() const
{
	if (userRepo != nullptr)
	{
		std::string listOfEvents = "\n";
		for (const auto& event : userRepo->events)
			listOfEvents += event.ToString() + '\n';

		return listOfEvents;
	}

	return "";
}
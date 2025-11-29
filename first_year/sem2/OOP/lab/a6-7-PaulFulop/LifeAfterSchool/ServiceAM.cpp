#include "ServiceAM.h"
#include <exception>

ServiceAM::ServiceAM() : repo { nullptr }, userRepo { nullptr }, eventViewer { nullptr }
{}

ServiceAM::ServiceAM(Repository* _repo, Repository* _userRepo, EventViewer* _eventViewer): repo { _repo }, userRepo { _userRepo }, eventViewer { _eventViewer }
{}

ServiceAM::~ServiceAM()
{
	delete repo;
}

void ServiceAM::AddEvent(Event new_event)
{
	if (repo != nullptr)
		repo->AddToRepo(new_event);
}

void ServiceAM::RemoveEvent(std::string title)
{
	Event event = Event();
	event.title = title;
	
	if (repo != nullptr)
	{
		repo->RemoveFromRepo(event);
		
		if (userRepo != nullptr)
			try {
				userRepo->RemoveFromRepo(event);
				eventViewer->StoreData();
			}
			catch (const std::exception& e) {
			}
	}
}

void ServiceAM::UpdateEvent(Event event, Event new_event)
{
	if (repo != nullptr)
	{
		repo->UpdateToRepo(event, new_event);

		if (userRepo != nullptr)
			try {
			userRepo->UpdateToRepo(event, new_event);
			eventViewer->StoreData();
		}
		catch (const std::exception& e) {
		}
	}
}

std::string ServiceAM::ListFilterEvents(int participants_filter) const
{
	if (repo != nullptr)
	{
		std::vector<Event> filteredEvents = repo->FilterEvents(participants_filter);
		std::string listOfFilteredEvents = "\n";
		for (const auto& event : filteredEvents)
			listOfFilteredEvents += event.ToString() + '\n';

		return listOfFilteredEvents;
	}

	return "";
}

std::string ServiceAM::ListOfEvents() const
{
	if (repo != nullptr)
	{
		std::string listOfEvents = "\n";
		for (const auto& event : repo->GetEvents())
			listOfEvents += event.ToString() + '\n';

		return listOfEvents;
	}

	return "";
}
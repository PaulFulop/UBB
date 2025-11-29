#include "ServiceAM.h"
#include <exception>

ServiceAM::ServiceAM() : repo { nullptr }, userRepo { nullptr }
{}

ServiceAM::ServiceAM(Repository* _repo, Repository* _userRepo): repo { _repo }, userRepo { _userRepo }
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
		}
		catch (const std::exception& e) {
		}
	}
}

int ServiceAM::FindEvent(Event event) {
	for (int i = 0; i < repo->events.size(); ++i) {
		if (repo->events[i] == event) return i;
	}

	throw InexistentEventException();
}
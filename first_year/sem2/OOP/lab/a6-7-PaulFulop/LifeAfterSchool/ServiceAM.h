#pragma once
#include "MemoryRepository.h"
#include "FileRepository.h"
#include "EventViewer.h"

class ServiceAM {
public:
    Repository* repo;
    Repository* userRepo;
	EventViewer* eventViewer;

    ServiceAM();
	ServiceAM(Repository* _repo, Repository* _userRepo, EventViewer* _eventViewer);
    ~ServiceAM();

	void AddEvent(Event new_event);
	void RemoveEvent(std::string title);
	void UpdateEvent(Event event, Event new_event);
    std::string ListFilterEvents(int participants_filter) const;
	std::string ListOfEvents() const;
};
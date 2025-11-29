#pragma once
#include "MemoryRepository.h"
#include "FileRepository.h"

class ServiceAM {
public:
    Repository* repo;
    Repository* userRepo;

    ServiceAM();
    ServiceAM(Repository* _repo, Repository* _userRepo);
    ~ServiceAM();

	void AddEvent(Event new_event);
	void RemoveEvent(std::string title);
	void UpdateEvent(Event event, Event new_event);
    int FindEvent(Event event);
};
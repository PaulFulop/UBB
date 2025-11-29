#pragma once
#include "Event.h"
#include "Repository.h"
#include <vector>
#include "EventExceptions.h"

class MemoryRepository : public Repository {
public:
    MemoryRepository();
    MemoryRepository(const MemoryRepository& other);
    void AddToRepo(Event new_event) override;
    void RemoveFromRepo(Event event) override;
    void UpdateToRepo(Event event, Event new_event) override;
    void Refresh() override {}
    std::vector<Event> GetEvents() override;
    std::vector<Event> FilterEvents(int participants_filter) const override;
    Repository* Clone() const override;
    MemoryRepository& operator=(const MemoryRepository& other);
};
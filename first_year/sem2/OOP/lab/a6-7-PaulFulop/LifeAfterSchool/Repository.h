#pragma once
#include "Event.h"
#include <vector>

class Repository {
public:
    std::vector<Event> events;
    Repository() : events { std::vector<Event>() } {}
    Repository(std::vector<Event> _events) : events { _events } {}
    virtual void AddToRepo(Event new_event) = 0;
    virtual void RemoveFromRepo(Event event) = 0;
    virtual void UpdateToRepo(Event event, Event new_event) = 0;
    virtual void Refresh() = 0;
    virtual std::vector<Event> GetEvents() = 0;
    virtual std::vector<Event> FilterEvents(int participants_filter) const = 0;
    virtual Repository* Clone() const = 0;
    virtual ~Repository() {}
};
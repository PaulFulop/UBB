#pragma once
#include "Repository.h"

class ServiceAM {
public:
	Repository repo;

 /**
     @brief ServiceAM object constructor
 **/
	ServiceAM();

 /**
     @brief Adds a new event
     @param new_event - the new event to be added
 **/
	void AddEvent(Event new_event);

 /**
     @brief Removes an event
     @param title - the title of the event to be removed
 **/
	void RemoveEvent(string title);

 /**
     @brief Updates an event
     @param event     - the event to be updated
     @param new_event - the new version of the event
 **/
	void UpdateEvent(Event event, Event new_event);

/**
    @brief Filters the events based on the number of participants
    @param participants_filter - a dynamic vector representing all the events that have stictly less participants than the user provided value
**/
    string ListFilterEvents(int participants_filter) const;

 /**
     @brief  Generates a string of all the events in the database.
     @retval  - string representation of a list with all the existing events.
 **/
	string ListOfEvents() const;
};
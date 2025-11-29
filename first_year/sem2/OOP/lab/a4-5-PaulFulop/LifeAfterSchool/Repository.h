#pragma once
#include "Event.h"
#include "DynamicVector.h"

//TODO potetially change the name of this with repository 
class Repository {
public:
	DynamicVector<Event> events;

 /**
     @brief Repository object constructor
 **/
	Repository();

    /**
        @brief Repository copy constructor
        @param other - the Repository object used for copying
    **/
    Repository(const Repository& other);

 /**
     @brief  Adds a new event to the repository
     @param  new_event - the new event to be added
     @retval           - true if the event has been added succsessfully, false otherwise
 **/
	bool AddToRepo(Event new_event);

 /**
     @brief  Removes an event from the repository
     @param  event - the event to be removed
     @retval       - true if the event has been removed succsessfully, false otherwise
 **/
	bool RemoveFromRepo(Event event);

 /**
     @brief  Updates an event in the repository
     @param  event     - the event to be updated
     @param  new_event - the updated version of the event
     @retval           - true if the event has been updated succsessfully, false otherwise
 **/
	bool UpdateToRepo(Event event, Event new_event);

/**
    @brief Filters the events by the number of participants
    @param  participants_filter - the number of participants 
    @retval                     - a dynamic vector representing all the events that have stictly less participants than the user provided value
**/
    DynamicVector<Event> FilterEvents(int participants_filter) const;

    /**
        @brief  operator= Copy assignment operator
        @param  other - the Repository object used for assignment
        @retval       - this object reference
    **/
    Repository& operator=(const Repository& other);
};
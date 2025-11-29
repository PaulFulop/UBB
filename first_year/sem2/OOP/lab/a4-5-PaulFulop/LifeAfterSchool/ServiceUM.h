#pragma once
#include "Repository.h"
#include <exception>

class ServiceUM {
public:
	Repository userRepo;
	Repository* globalRepo;

 /**
     @brief ServiceUM object constructor
     @param _globalRepo - the pointer to the global repo
 **/
	ServiceUM(Repository* _globalRepo);

 /**
     @brief ServiceUM object destructor
 **/
	~ServiceUM();

 /**
     @brief Adds a new event for the user list
     @param pos - the position of the event in the global repo
 **/
	void AddUserEvent(int pos);

 /**
     @brief Removes an event from the user list
     @param title - the title of the event to be removed
 **/
	void RemoveUserEvent(string title);

 /**
     @brief Sorts the events from the repo parameter by date
     @param repo - the repository that has to be sorted
 **/
	void SortEventsByDate(Repository& repo) const;

 /**
     @brief  returns a repository containing all the events that take place in a certain month
     @param  month - the event filter
     @retval       - a repository containing all the evnts that take place in that month
 **/
	Repository GetEventsByMonth(int month) const;

 /**
     @brief  used for displaying the events
     @retval  - a string containing all events in the user list
 **/
	string ListUserEvents() const;
};
#pragma once
#include <string>
#include "EventValidator.h"

class Event {
public:
	std::string title, description, dt, link;
	int nr_of_people;
	
/**
	@brief Event object constructor
**/
	Event();

/**
	@brief Event object constructor
	@param title        - the title of the event (unique id)
	@param description  - the description of the event
	@param dt           - the date and time of the event
	@param nr_of_people - the numbber of people participating to the event
	@param link         - the link to the online resources of the event
**/
	Event(std::string title, std::string description, std::string dt, int nr_of_people, std::string link);

 /**
     @brief Event object constructor
     @param other - the Event object used for copying
 **/
	Event(const Event& other);

/**
	@brief  Converts an event to its string representation
	@retval  - A string representation of the event
**/
	std::string ToString() const;

/**
	@brief  operator== Equal operator for the object. Two events are equal if their title is the same
	@param  e - the event used for comparison
	@retval   - true if objects are equal, false otherwise
**/
	bool operator==(const Event& e) const noexcept;

/**
	@brief  operator= Assignment operator for the class
	@param  e - The event that will be copied.
	@retval   - the reference of this object
**/
	Event& operator=(const Event& e) noexcept;

	friend std::istream& operator >> (std::istream& is, Event& e);
	friend std::ostream& operator << (std::ostream& os, const Event& e);
};
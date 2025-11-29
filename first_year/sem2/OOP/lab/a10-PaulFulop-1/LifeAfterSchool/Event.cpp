#include "Event.h"
#include "Utils.h"
#include <vector>
#include <iostream>

Event::Event(): title {""}, description {""}, dt {""}, nr_of_people {0}, link {""}
{}

Event::Event(std::string _title, std::string _description, std::string _dt, int _nr_of_people, std::string _link) : title{_title}, description{_description},
dt{_dt}, nr_of_people{_nr_of_people}, link{_link}
{
	EventValidator::Validate(*this);
}

Event::Event(const Event& other)
{
	title = other.title;
	description = other.description;
	dt = other.dt;
	nr_of_people = other.nr_of_people;
	link = other.link;
}

std::string Event::ToString() const
{
	std::string strEvent = "";
	strEvent += "Title: " + title + '\n';
	strEvent += "Description: " + description + '\n';
	strEvent += "Date and Time: " + dt + '\n';
	strEvent += "Number of participants: " + std::to_string(nr_of_people) + '\n';
	strEvent += "Link: " + link + '\n';

	return strEvent;
}

bool Event::operator == (const Event& e) const noexcept
{
	return title == e.title;
}

Event& Event::operator = (const Event& e) noexcept
{
	title = e.title;
	description = e.description;
	dt = e.dt;
	nr_of_people = e.nr_of_people;
	link = e.link;

	return *this;
}

std::istream& operator >> (std::istream& is, Event& e)
{
	std::string eventString;
	getline(is, eventString);
	std::vector<std::string> tokens = Tokenize(eventString, ',');
	
	if (tokens.size() != 5)
		return is;

	Event eventCopy = Event(tokens[0], tokens[1], tokens[2], stoi(tokens[3]), tokens[4]);
	e = eventCopy;
	return is;
}

std::ostream& operator << (std::ostream& os, const Event& e)
{
	os << e.title << ',' << e.description << ',' << e.dt << ',' << e.nr_of_people << ',' << e.link;
	return os;
}
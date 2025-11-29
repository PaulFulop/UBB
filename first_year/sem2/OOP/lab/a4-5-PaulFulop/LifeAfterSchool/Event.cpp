#include "Event.h"

Event::Event(): title {""}, description {""}, dt {""}, nr_of_people {0}, link {""}
{}

Event::Event(string _title, string _description, string _dt, int _nr_of_people, string _link) : title{_title}, description{_description},
dt{_dt}, nr_of_people{_nr_of_people}, link{_link}
{}

Event::Event(const Event& other)
{
	title = other.title;
	description = other.description;
	dt = other.dt;
	nr_of_people = other.nr_of_people;
	link = other.link;
}

string Event::ToString() const
{
	string strEvent = "";
	strEvent += "Title: " + title + '\n';
	strEvent += "Description: " + description + '\n';
	strEvent += "Date and Time: " + dt + '\n';
	strEvent += "Number of participants: " + to_string(nr_of_people) + '\n';
	strEvent += "Link: " + link + '\n';

	return strEvent;
}

bool Event::ValidDT() const
{
	if (dt.size() != 10) return false;
	if (dt[2] != '/' || dt[5] != '/') return false;
	if (!isdigit(dt[0]) || !isdigit(dt[1]) || !isdigit(dt[3]) || !isdigit(dt[4]) ||
		!isdigit(dt[6]) || !isdigit(dt[7]) || !isdigit(dt[8]) || !isdigit(dt[9]))
		return false;
	
	int month = (dt[0] - 48) * 10 + dt[1] - 48;
	if (month > 12) return false;

	int day = (dt[3] - 48) * 10 + dt[4] - 48;
	if (day > 30) return false;

	return true;
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
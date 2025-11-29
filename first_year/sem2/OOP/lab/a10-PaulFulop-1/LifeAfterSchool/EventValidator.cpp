#include "EventValidator.h"
#include "Event.h"

void EventValidator::Validate(const Event& event)
{
	if (!ValidateDate(event))
		throw InvalidDateException();

	if (!ValidateLink(event))
		throw InvalidLinkException();

	if (!ValidateNrOfParticipants(event))
		throw NegativeNrOfParticipantsException();
}


bool EventValidator::ValidateDate(const Event& event) noexcept
{
	if (event.dt.size() != 10) return false;
	if (event.dt[2] != '/' || event.dt[5] != '/') return false;
	if (!isdigit(event.dt[0]) || !isdigit(event.dt[1]) || !isdigit(event.dt[3]) || !isdigit(event.dt[4]) ||
		!isdigit(event.dt[6]) || !isdigit(event.dt[7]) || !isdigit(event.dt[8]) || !isdigit(event.dt[9]))
		return false;

	int month = (event.dt[0] - 48) * 10 + event.dt[1] - 48;
	if (month > 12) return false;

	int day = (event.dt[3] - 48) * 10 + event.dt[4] - 48;
	if (day > 30) return false;

	return true;
}

bool EventValidator::ValidateLink(const Event& event) noexcept
{
	
	return event.link.substr(0, 8) == "https://";
}

bool EventValidator::ValidateNrOfParticipants(const Event& event) noexcept
{
	return event.nr_of_people >= 0;
}
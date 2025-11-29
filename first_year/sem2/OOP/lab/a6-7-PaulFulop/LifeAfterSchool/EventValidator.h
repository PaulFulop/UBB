#pragma once
#include "EventExceptions.h"

class Event;

class EventValidator {
public:
	static void Validate(const Event& event);
private:
	static bool ValidateDate(const Event& event) noexcept;
	static bool ValidateNrOfParticipants(const Event& event) noexcept;
	static bool ValidateLink(const Event& event) noexcept;
};
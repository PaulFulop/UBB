#pragma once
#include <exception>
#include <string>

class EventException : public std::exception {
public:
	virtual const char* what() const noexcept override = 0;
};

class DuplicateEventException : public EventException {
public:
	const char* what() const noexcept override {
		return "This event already exists!";
	}
};

class InexistentEventException : public EventException {
public:
	const char* what() const noexcept override {
		return "The event has not been found!";
	}
};

class InvalidDateException : public EventException {
public:
	const char* what() const noexcept override {
		return "Invalid date!";
	}
};

class NegativeNrOfParticipantsException : public EventException {
public:
	const char* what() const noexcept override {
		return "The number of participants cannot be negative!";
	}
};

class InvalidLinkException : public EventException {
public:
	const char* what() const noexcept override {
		return "Invalid link!";
	}
};

class OutOfRangeException : public EventException {
public:
	const char* what() const noexcept override {
		return "Out of range!";
	}
};

class EventsFileException : public EventException {
public:
	const char* what() const noexcept override {
		return "The file containing all the events could not be opened!";
	}
};
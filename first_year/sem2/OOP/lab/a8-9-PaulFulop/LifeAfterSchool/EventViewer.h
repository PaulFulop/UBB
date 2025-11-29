#pragma once
#include "Event.h"
#include <vector>
#include <string>
#include <fstream>
#include "EventExceptions.h"

class EventViewer {
protected:
	std::vector<Event>* events;
	std::string outputFileDescriptor;
public:
	EventViewer(std::vector<Event>* _events, std::string _outputFileDescriptor) : events{ _events }, outputFileDescriptor{ _outputFileDescriptor } {}
	virtual ~EventViewer() { events = nullptr; delete events; }
	virtual void StoreData() const = 0;
	void Clear() const {
		std::ofstream fout(outputFileDescriptor);

		if (!fout.is_open())
			throw EventsFileException();

		fout << "";
		fout.close();
	}
	virtual std::string GetFile() const = 0;
};
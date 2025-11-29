#pragma once
#include "EventViewer.h"
#include "EventExceptions.h"

class HTMLEventViewer : public EventViewer {
public:
	HTMLEventViewer(std::vector<Event>* _events, std::string _outputFileDescriptor);
	void StoreData() const override;
	std::string GetFile() const override;
};
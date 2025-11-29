#pragma once
#include "EventViewer.h"
#include "EventExceptions.h"

class CSVEventViewer : public EventViewer {
public:
	CSVEventViewer(std::vector<Event>* _events, std::string _outputFileDescriptor);
	void StoreData() const override;
	std::string GetFile() const override;
};
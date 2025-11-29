#include "CSVEventViewer.h"
#include <fstream>

CSVEventViewer::CSVEventViewer(std::vector<Event>* _events, std::string _outputFileDescriptor) : EventViewer(_events, _outputFileDescriptor) { StoreData(); }

void CSVEventViewer::StoreData() const
{
	std::ofstream fout(outputFileDescriptor);

	if (!fout.is_open())
		throw EventsFileException();

	if (events != nullptr)
		for (const auto& event : *events)
			fout << event << '\n';

	fout.close();
}

std::string CSVEventViewer::GetFile() const
{
	return outputFileDescriptor;
}
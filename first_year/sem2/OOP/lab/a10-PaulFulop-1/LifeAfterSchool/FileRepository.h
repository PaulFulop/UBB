#pragma once
#include "Repository.h"
#include <string>
#include "EventExceptions.h"

class FileRepository : public Repository {
public:
    FileRepository();
    FileRepository(std::string _fileDescriptor);
    FileRepository(const FileRepository& other);

    void AddToRepo(Event new_event) override;
    void RemoveFromRepo(Event event) override;
    void UpdateToRepo(Event event, Event new_event) override;
    void Refresh() override;
    std::vector<Event> GetEvents() override;
    std::vector<Event> FilterEvents(int participants_filter) const override;
    Repository* Clone() const override;
    FileRepository& operator=(const FileRepository& other);

private:
    std::string fileDescriptor;
    void SaveToFile();
    void ReadFromFile();
};
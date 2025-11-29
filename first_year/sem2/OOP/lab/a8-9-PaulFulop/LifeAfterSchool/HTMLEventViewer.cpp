#include "HTMLEventViewer.h"
#include <fstream>

HTMLEventViewer::HTMLEventViewer(std::vector<Event>* _events, std::string _outputFileDescriptor) : EventViewer(_events, _outputFileDescriptor) { StoreData(); }

void HTMLEventViewer::StoreData() const
{
    std::ofstream fout(outputFileDescriptor);

    if (!fout.is_open())
        throw EventsFileException();

    if (events != nullptr)
    {
        fout << "<!DOCTYPE html>\n";
        fout << "<html>\n";
        fout << "<head>\n";
        fout << "    <title>Event Manager</title>\n";
        fout << "</head>\n";
        fout << "<body>\n";
        fout << "<table border=\"1\">\n";
        fout << "    <tr>\n";
        fout << "        <td>Title</td>\n";
        fout << "        <td>Description</td>\n";
        fout << "        <td>Date</td>\n";
        fout << "        <td>Number of People</td>\n";
        fout << "        <td>Link</td>\n";
        fout << "    </tr>\n";

        for (const auto& event : *events) {
            fout << "    <tr>\n";
            fout << "        <td>" << event.title << "</td>\n";
            fout << "        <td>" << event.description << "</td>\n";
            fout << "        <td>" << event.dt << "</td>\n";
            fout << "        <td>" << event.nr_of_people << "</td>\n";
            fout << "        <td><a href=\"" << event.link << "\">Link</a></td>\n";
            fout << "    </tr>\n";
        }

        fout << "</table>\n";
        fout << "</body>\n";
        fout << "</html>\n";
    }
}

std::string HTMLEventViewer::GetFile() const
{
    return outputFileDescriptor;
}
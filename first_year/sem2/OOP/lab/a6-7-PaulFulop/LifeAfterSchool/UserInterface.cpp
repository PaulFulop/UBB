#include "UserInterface.h"
#include <iostream>
#include <cstring>

UserInterface::UserInterface(std::vector<std::string> _fileDescriptors) : fileDescriptors {_fileDescriptors}
{
	InitializeData();
}

bool UserInterface::Mode()
{
	char mode = '\0';
	std::string text = "";

	while (mode != 'a' && mode != 'u')
	{
		system("cls");
		std::cout << "EVENT MANAGER\n" << text << "\nChoose mode (a -> admin mode / u -> user mode): ";
		if (std::cin.peek() == '\n')
			std::cin.get();
		std::cin.get(mode);

		if (mode < 'a') mode += 32;
		if (std::cin.peek() != '\n') mode = '\0';

		text = "\nInvalid mode.\n";
		std::cin.ignore(10000, '\n');
	}

	return mode == 'a' ? true : false;
}

void UserInterface::PrintAdminMenu()
{
	std::cout << "EVENT MANAGER\n\n1 -> Add a new event to the list\n2 -> Remove an event from the list\n3 -> Update an event from the list\n4 -> Display all events\n5 -> Filter the events by number of participants\n6 -> Choose mode\n7 -> Exit\n";
}

void UserInterface::PrintUserMenu()
{
	std::cout << "EVENT MANAGER\n\n1 -> Choose from events happening during a given month.\n2 -> Delete an event from your list.\n3 -> Display the list of events you want to attend to.\n4 -> See your list of events.\n5 -> Choose mode\n6 -> Exit.\n";
}

void UserInterface::PrintUserCommands()
{
	std::cout << "\n\ny -> add the current event to your list\nn -> ignore the current event\ne -> exit\n";
}

void UserInterface::RunAdminMenu()
{
	std::string text, title, description, link, dt;
	int nr_of_people = 0;
	int cmd = 0;
	bool running = true, chooseMode;

	while (running)
	{
		system("cls");
		PrintAdminMenu();
		std::cout << text << "\n> ";

		if (std::cin.peek() == '\n')
		{
			std::cin.get();
			continue;
		}

		std::cin >> cmd;

		if (std::cin.fail() || std::cin.peek() != '\n') {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			cmd = 0;
		}

		chooseMode = false;
		switch (cmd)
		{
			case 1:
				try {
					std::cout << "Insert the title of the event: ";
					std::cin >> title;

					std::cout << "Insert the description of the event: ";
					std::cin >> description;

					std::cout << "Insert the date and time of the event (mm/dd/yyyy): ";
					std::cin >> dt;

					std::cout << "Insert the number of participants: ";
					std::cin >> nr_of_people;

					std::cout << "Insert the link towards the online resource containing the event: ";
					std::cin >> link;

					adminServ.AddEvent(Event(title, description, dt, nr_of_people, link));
					text = "\nThe new event has been added.\n";
				}
				catch (const std::exception& e){
					text = e.what();
					text.insert(0, "\n");
				}
				break;
			case 2:
				try {
					std::cout << "Insert the title of the event you want to remove: ";
					std::cin >> title;

					adminServ.RemoveEvent(title);
					text = "\nThe event has been removed.\n";
				}
				catch (const std::exception& e) {
					text = e.what();
					text.insert(0, "\n");
				}
				break;
			case 3:
				try {
					std::cout << "Insert the title of the event you want to update: ";
					std::cin >> title;
					
					Event auxEvent = Event(), newEvent = Event();
					auxEvent.title = title;
					newEvent.title = title;

					std::cout << "Insert the new description: ";
					std::cin >> newEvent.description;

					std::cout << "Insert the new date: ";
					std::cin >> newEvent.dt;

					std::cout << "Insert the new number of participants: ";
					std::cin >> newEvent.nr_of_people;

					std::cout << "Insert the new link: ";
					std::cin >> newEvent.link;

					adminServ.UpdateEvent(auxEvent, newEvent);
					text = "\nThe event has been updated.\n";
				}
				catch (const std::exception& e) {
					text = e.what();
					text.insert(0, "\n");
				}
				break;
			case 4:
				text = adminServ.ListOfEvents();
				if (text == "\n")
					text = "\nNo events.\n";
				break;
			case 5:
				try {
					int participants;
					std::cout << "Insert the number of participants for the filter: ";
					std::cin >> participants;

					if (participants <= 0)
						throw NegativeNrOfParticipantsException();
					text = adminServ.ListFilterEvents(participants);
				}
				catch (const std::exception& e) {
					text = e.what();
					text.insert(0, "\n");
				}
				break;
			case 6:
				chooseMode = true;
				running = false;
				break;
			case 7:
				std::cout << "Exiting...\n";
				running = false;
				break;
			default:
				text = "\nInvalid command.\n";
				break;
		}
	}

	if (chooseMode)
		Start();
}

void UserInterface::RunUserMenu()
{
	Event eventCopy;
	std::string text = "", text1 = "", title = "", openLink = "", openFile = "";
	int cmd = 0;
	bool running = true, chooseMode;

	while (running)
	{
		system("cls");
		PrintUserMenu();
		std::cout << text << "\n> ";

		if (std::cin.peek() == '\n')
		{
			std::cin.get();
			continue;
		}

		std::cin >> cmd;

		if (std::cin.fail() || std::cin.peek() != '\n') {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			cmd = 0;
		}

		std::cin.get();

		chooseMode = false;
		switch (cmd)
		{
		case 1:
			try {
				Repository* filteredEvents = nullptr;
				int month = 0, pos = 0, pos1 = 0;
				char userChoice;
				bool displayingEvents = true;
				text = text1 = "";

				std::cout << "Insert the month of the events you want to see here: ";
				if (std::cin.peek() == '\n' && userServ.globalRepo != nullptr)
				{
					filteredEvents = userServ.globalRepo->Clone();
					userServ.SortEventsByDate(filteredEvents);
				}

				if (std::cin.peek() != '\n')
				{
					std::cin >> month;
					filteredEvents = userServ.GetEventsByMonth(month);
				}

				if (std::cin.peek() != '\n' || std::cin.fail() || filteredEvents == nullptr || !filteredEvents->GetEvents().size())
				{ 
					std::cin.clear();
					std::cin.ignore(10000, '\n');
					text = "\nNo events.\n";
					continue;
				}

				std::cin.get();
				while (pos < filteredEvents->GetEvents().size() && displayingEvents)
				{
					system("cls");
					std::cout << filteredEvents->GetEvents()[pos].ToString();
					PrintUserCommands();
					std::cout << text1 << "\n> ";
					openLink = "start " + filteredEvents->GetEvents()[pos].link;
					//system(openLink.c_str());

					userChoice = std::cin.get();
					if (std::cin.get() != '\n')
					{
						userChoice = '\0';
						std::cin.ignore(10000, '\n');
					}

					switch (userChoice)
					{
					case 'y':
						try {
							pos1 = 0;
							for (const auto& event : userServ.globalRepo->GetEvents())
							{
								if (event == filteredEvents->GetEvents()[pos])
									break;
								++pos1;
							}
							userServ.AddUserEvent(pos1);
							text1 = "\nThe previous event has been added.\n";
						}
						catch (const std::exception& e) {
							text1 = e.what();
							text1.insert(0, "\n");
						}
						break;
					case 'n':
						text1 = "\nThe previous event has not been added.\n";
						break;
					case 'e':
						displayingEvents = false;
						break;
					default:
						text1 = "\nInvalid command.\n";
						if (pos)
							--pos;
						break;
					}

					pos = (pos + 1) % filteredEvents->GetEvents().size();
				}

				delete filteredEvents;
			}
			catch (const std::exception& e) {
				text = e.what();
				text.insert(0, "\n");
			}
			break;
		case 2:
			try {
				std::cout << "Insert the title of the event you want to remove: ";
				std::cin >> title;

				userServ.RemoveUserEvent(title);
				text = "\nThe event has been removed.\n";
			}
			catch (const std::exception& e) {
				text = e.what();
				text.insert(0, "\n");
			}
			break;
		case 3:
			try {
				text = userServ.ListUserEvents();
				if (text == "\n")
					text = "\nNo events.\n";
			}
			catch (const std::exception& e) {
				text = e.what();
				text.insert(0, "\n");
			}
			break;
		case 4:
			openFile = "start " + userServ.eventViewer->GetFile();
			system(openFile.c_str());
			text = "\nYour list of events has been opened from " + userServ.eventViewer->GetFile() + ". IF YOU'RE USING CSV FILES AS OUTPUT PLEASE CLOSE EXCEL BEFORE EXITING COMPLETELY.\n";
			break;
		case 5:
			chooseMode = true;
			running = false;
			break;
		case 6:
			std::cout << "Exiting...\n";
			running = false;
			break;
		default:
			text = "\nInvalid command.\n";
			break;
		}
	}

	if (chooseMode)
		Start();
}

void UserInterface::Start()
{
	bool mode = Mode();

	if (mode)
		RunAdminMenu();
	else
		RunUserMenu();
}

void UserInterface::InitializeData()
{
	int option = 0;
	while (true)
	{
		system("cls");
		std::cout << "Enter repository type (1 -> memory with csv output, 2 -> memory with html output, 3 -> file with csv output, 4 -> file with html output): ";
		if (std::cin.peek() == '\n') {
			std::cin.get();
			continue;
		}

		std::cin >> option;
		if ((std::cin.fail() || std::cin.peek() != '\n') || (option != 1 && option != 2 && option != 3 && option != 4)) {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
		else
			break;
	}

	switch (option) {
	case 1:
		adminServ.repo = new MemoryRepository;
		userServ.userRepo = new MemoryRepository;
		adminServ.userRepo = userServ.userRepo;
		userServ.globalRepo = adminServ.repo;
		userServ.eventViewer = new CSVEventViewer(&userServ.userRepo->events, fileDescriptors[2]); 
		adminServ.eventViewer = userServ.eventViewer;
		AddEvents(*adminServ.repo);
		break;
	case 2:
		adminServ.repo = new MemoryRepository;
		userServ.userRepo = new MemoryRepository;
		adminServ.userRepo = userServ.userRepo;
		userServ.globalRepo = adminServ.repo;
		userServ.eventViewer = new HTMLEventViewer(&userServ.userRepo->events, fileDescriptors[3]);
		adminServ.eventViewer = userServ.eventViewer;
		AddEvents(*adminServ.repo);
		break;
	case 3:
		adminServ.repo = new FileRepository(fileDescriptors[0]);
		userServ.userRepo = new FileRepository(fileDescriptors[1]);
		adminServ.userRepo = userServ.userRepo;
		userServ.globalRepo = adminServ.repo;
		userServ.eventViewer = new CSVEventViewer(&userServ.userRepo->events, fileDescriptors[2]);
		adminServ.eventViewer = userServ.eventViewer;
		break;
	case 4:
		adminServ.repo = new FileRepository(fileDescriptors[0]);
		userServ.userRepo = new FileRepository(fileDescriptors[1]);
		adminServ.userRepo = userServ.userRepo;
		userServ.globalRepo = adminServ.repo;
		userServ.eventViewer = new HTMLEventViewer(&userServ.userRepo->events, fileDescriptors[3]);
		adminServ.eventViewer = userServ.eventViewer;
		break;
	}
}

UserInterface::~UserInterface()
{}

void UserInterface::AddEvents(Repository& repo)
{
	repo.AddToRepo(Event("title1", "desc1", "03/22/2025", 102, "https://github.com/cs-ubbcluj-ro/a4-5-PaulFulop"));
	repo.AddToRepo(Event("title2", "desc2", "03/30/2022", 1203, "https://github.com/cs-ubbcluj-ro/a4-5-PaulFulop"));
	repo.AddToRepo(Event("title3", "desc3", "04/17/2024", 52, "https://github.com/cs-ubbcluj-ro/a4-5-PaulFulop"));
	repo.AddToRepo(Event("title4", "desc4", "08/22/2020", 50000, "https://github.com/cs-ubbcluj-ro/a4-5-PaulFulop"));
	repo.AddToRepo(Event("title5", "desc5", "10/13/2025", 402145, "https://github.com/cs-ubbcluj-ro/a4-5-PaulFulop"));
	repo.AddToRepo(Event("title6", "desc6", "01/17/2018", 219844, "https://github.com/cs-ubbcluj-ro/a4-5-PaulFulop"));
	repo.AddToRepo(Event("title7", "desc7", "11/01/2023", 21055952, "https://github.com/cs-ubbcluj-ro/a4-5-PaulFulop"));
	repo.AddToRepo(Event("title8", "desc8", "02/09/2023", 123124, "https://github.com/cs-ubbcluj-ro/a4-5-PaulFulop"));
	repo.AddToRepo(Event("title9", "desc9", "02/27/2025", 3123, "https://github.com/cs-ubbcluj-ro/a4-5-PaulFulop"));
	repo.AddToRepo(Event("title10", "desc10", "01/26/2025", 11122, "https://github.com/cs-ubbcluj-ro/a4-5-PaulFulop"));
}
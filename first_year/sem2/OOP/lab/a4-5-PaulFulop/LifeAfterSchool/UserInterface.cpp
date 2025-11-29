#include "UserInterface.h"
#include <iostream>
#include <cstring>

UserInterface::UserInterface(): adminServ {ServiceAM()}, userServ {ServiceUM(&adminServ.repo)}
{}

bool UserInterface::Mode()
{
	char mode = '\0';
	string text = "";

	while (mode != 'a' && mode != 'u')
	{
		system("cls");
		cout << "EVENT MANAGER\n" << text << "\nChoose mode (a -> admin mode / u -> user mode): ";
		if (cin.peek() == '\n')
			cin.get();
		cin.get(mode);

		if (mode < 'a') mode += 32;
		if (cin.peek() != '\n') mode = '\0';

		text = "\nInvalid mode.\n";
		cin.ignore(10000, '\n');
	}

	return mode == 'a' ? true : false;
}

void UserInterface::PrintAdminMenu()
{
	cout << "EVENT MANAGER\n\n1 -> Add a new event to the list\n2 -> Remove an event from the list\n3 -> Update an event from the list\n4 -> Display all events\n5 -> Filter the events by number of participants\n6 -> Choose mode\n7 -> Exit\n";
}

void UserInterface::PrintUserMenu()
{
	cout << "EVENT MANAGER\n\n1 -> Choose from events happening during a given month.\n2 -> Delete an event from your list.\n3 -> Display the list of events you want to attend to.\n4 -> Choose mode\n5 -> Exit.\n";
}

void UserInterface::PrintUserCommands()
{
	cout << "\n\ny -> add the current event to your list\nn -> ignore the current event\ne -> exit\n";
}

void UserInterface::RunAdminMenu()
{
	string text, title;
	int cmd = 0;
	bool running = true, chooseMode;

	while (running)
	{
		system("cls");
		PrintAdminMenu();
		cout << text << "\n> ";

		if (cin.peek() == '\n')
		{
			cin.get();
			continue;
		}

		cin >> cmd;

		if (cin.fail() || cin.peek() != '\n') {
			cin.clear();
			cin.ignore(10000, '\n');
			cmd = 0;
		}

		chooseMode = false;
		switch (cmd)
		{
			case 1:
				try {
					Event newEvent = Event();
					cout << "Insert the title of the event: ";
					cin >> newEvent.title;

					cout << "Insert the description of the event: ";
					cin >> newEvent.description;

					cout << "Insert the date and time of the event (mm/dd/yyyy): ";
					cin >> newEvent.dt;

					if (!newEvent.ValidDT())
						throw exception("Invalid date.\n");


					cout << "Insert the number of participants: ";
					cin >> newEvent.nr_of_people;

					if (newEvent.nr_of_people < 0)
						throw exception("Invalid number of people.\n");

					cout << "Insert the link towards the online resource containing the event: ";
					cin >> newEvent.link;

					adminServ.AddEvent(newEvent);
					text = "\nThe new event has been added.\n";
				}
				catch (const exception& e){
					text = e.what();
					text.insert(0, "\n");
				}
				break;
			case 2:
				try {
					cout << "Insert the title of the event you want to remove: ";
					cin >> title;

					adminServ.RemoveEvent(title);
					text = "\nThe event has been removed.\n";
				}
				catch (const exception& e) {
					text = e.what();
					text.insert(0, "\n");
				}
				break;
			case 3:
				try {
					cout << "Insert the title of the event you want to update: ";
					cin >> title;
					
					Event auxEvent = Event(), newEvent = Event();
					auxEvent.title = title;
					newEvent.title = title;

					cout << "Insert the new description: ";
					cin >> newEvent.description;

					cout << "Insert the new date: ";
					cin >> newEvent.dt;

					if (!newEvent.ValidDT())
						throw exception("Invalid date.\n");

					cout << "Insert the new number of participants: ";
					cin >> newEvent.nr_of_people;

					if (newEvent.nr_of_people < 0)
						throw exception("Invalid number of people.\n");

					cout << "Insert the new link: ";
					cin >> newEvent.link;

					adminServ.UpdateEvent(auxEvent, newEvent);
					text = "\nThe event has been updated.\n";
				}
				catch (const exception& e) {
					text = e.what();
					text.insert(0, "\n");
				}
				break;
			case 4:
				text = adminServ.ListOfEvents();
				if (text == "")
					text = "\nNo events.\n";
				break;
			case 5:
				try {
					int participants;
					cout << "Insert the number of participants for the filter: ";
					cin >> participants;

					if (participants <= 0)
						throw exception("Invalid number of participants.\n");
					text = adminServ.ListFilterEvents(participants);
				}
				catch (const exception& e) {
					text = e.what();
					text.insert(0, "\n");
				}
				break;
			case 6:
				chooseMode = true;
				running = false;
				break;
			case 7:
				cout << "Exiting...\n";
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
	string text = "", text1 = "", title = "", openLink = "";
	int cmd = 0;
	bool running = true, chooseMode;

	while (running)
	{
		system("cls");
		PrintUserMenu();
		cout << text << "\n> ";

		if (cin.peek() == '\n')
		{
			cin.get();
			continue;
		}

		cin >> cmd;

		if (cin.fail() || cin.peek() != '\n') {
			cin.clear();
			cin.ignore(10000, '\n');
			cmd = 0;
		}

		cin.get();

		chooseMode = false;
		switch (cmd)
		{
		case 1:
			try {
				Repository filteredEvents;
				int month, pos = 0, pos1 = 0;
				char userChoice;
				bool displayingEvents = true;
				text = text1 = "";

				cout << "Insert the month of the events you want to see here: ";
				if (cin.peek() == '\n')
				{
					cin.get();
					filteredEvents = *userServ.globalRepo;
					userServ.SortEventsByDate(filteredEvents);
				}
				else
				{
					cin >> month;
					filteredEvents = userServ.GetEventsByMonth(month);
				}

				cin.get();
				if (!filteredEvents.events.length)
					throw exception("No events.\n");

				while (pos < filteredEvents.events.length && displayingEvents)
				{
					system("cls");
					cout << filteredEvents.events.data[pos].ToString();
					PrintUserCommands();
					cout << text1 << "\n> ";
					openLink = "start " + filteredEvents.events.data[pos].link;
					system(openLink.c_str());

					userChoice = cin.get();
					if (cin.get() != '\n')
					{
						userChoice = '\0';
						cin.ignore(10000, '\n');
					}

					switch (userChoice)
					{
					case 'y':
						try {
							for (int i = 0; i < userServ.globalRepo->events.length; ++i)
								if (userServ.globalRepo->events.data[i] == filteredEvents.events.data[pos])
								{
									pos1 = i;
									break;
								}
							userServ.AddUserEvent(pos1);
							++userServ.userRepo.events.data[userServ.userRepo.events.length - 1].nr_of_people;
							text1 = "\nThe previous event has been added.\n";
						}
						catch (const exception& e) {
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

					pos = (pos + 1) % filteredEvents.events.length;
				}

			}
			catch (const exception& e) {
				text = e.what();
				text.insert(0, "\n");
			}
			break;
		case 2:
			try {
				cout << "Insert the title of the event you want to remove: ";
				cin >> title;

				userServ.RemoveUserEvent(title);
				text = "\nThe event has been removed.\n";
			}
			catch (const exception& e) {
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
			catch (const exception& e) {
				text = e.what();
				text.insert(0, "\n");
			}
			break;
		case 4:
			chooseMode = true;
			running = false;
			break;
		case 5:
			cout << "Exiting...\n";
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
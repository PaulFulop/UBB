#include "UI.h"
#include <iostream>

UI::UI() : serv{ Service() }
{}

void UI::PrintCommands()
{
	cout << "1 -> remove a school\n2 -> display all schools sorted by name\n3 -> mark all schools before date as visited and display the visited ones after the date\n4 -> exit\n\n";
}

void UI::StartMenu()
{
	int cmd;
	string date, name;
	pair<double, double> address;
	bool running = true;

	PrintCommands();
	
	while (running)
	{
		cout << "\n> ";
		cin >> cmd;

		switch (cmd)
		{
		case 1:
			try {
				cout << "Insert the name here: ";
				cin >> name;

				cout << "Insert the first cord of the address here: ";
				cin >> address.first;

				cout << "Insert the second cord of the address here: ";
				cin >> address.second;

				serv.RemoveSchool(name, address);
				cout << "Address removed.\n";
			}
			catch (const exception& e){
				cout << e.what() << "\n";
			}
			break;
		case 2:
			cout << serv.DisplaySchools();
			break;
		case 3:
			cout << "Inssert the date here: ";
			cin >> date;
			cout << serv.MarkDisplaySchools(date);
			break;
		case 4:
			cout << "Exiting...\n";
			running = false;
			break;
		}
	}
}
#include "UI.h"
#include <iostream>
#include "Refrigerator.h"
#include "DishWasher.h"

void UI::InitData()
{
	Refrigerator* r1 = new Refrigerator("id1", "A++", true);
	Refrigerator* r2 = new Refrigerator("id2", "A", false);
	DishWasher* d1 = new DishWasher("id3", 0.4);
	DishWasher* d2 = new DishWasher("id3", 1.2);

	serv.AddAppliance(r1);
	serv.AddAppliance(r2);
	serv.AddAppliance(d1);
	serv.AddAppliance(d2);
}

void UI::PrintCommands()
{
	std::cout << "Commands:\n1 -> add a new appliance\n2 -> show all appliances\n3 -> show all inefficient aplliances\n4 -> save to file appliances that have less consumed electricity than a given value\n5 -> exit\n";
}

void UI::Start()
{
	InitData();
	PrintCommands();
	int cmd = 0, value;
	bool choice, freezer;
	std::string rclass, id;
	double quantity;
	std::vector<Appliance*> a;

	while (true)
	{
		std::cout << "\n> ";
		std::cin >> cmd;

		switch (cmd)
		{
		case 1:
			std::cout << "Insert the id of the new appliance: ";
			std::cin >> id;
			std::cout << "Insert the appliance type (0 -> dish washer, 1 -> refrigerator): ";
			std::cin >> choice;

			if (choice)
			{
				std::cout << "Insert the refrigerator class here (A / A++): ";
				std::cin >> rclass;
				std::cout << "Does it have refrigerator? (1 -> yes / 0 -> no) ";
				std::cin >> freezer;
				
				Refrigerator* r = new Refrigerator(id, rclass, freezer);
				serv.AddAppliance(r);
			}
			else
			{
				std::cout << "Insert the quantity per hour: ";
				std::cin >> quantity;

				DishWasher* d = new DishWasher(id, quantity);
				serv.AddAppliance(d);
			}
			break;
		case 2:
			a = serv.GetAllAppliances();
			for (const auto& appliance : a)
				std::cout << appliance->toString() << '\n';
			break;
		case 3:
			a = serv.GetInefficientAppliances();
			for (const auto& appliance : a)
				std::cout << appliance->toString() << '\n';
			break;
		case 4:
			std::cout << "Insert the value of max quantity: ";
			std::cin >> quantity;
			a = serv.GetAppliancesLessThanValue(quantity);
			serv.SortAppliances(a);
			serv.WriteToFile("appliances.txt", a);
			std::cout << "Wrote to file.\n";
			break;
		case 5:
			std::cout << "Exiting...\n\n";
			exit(0);
			break;
		default:
			std::cout << "Invalid command.\n";
			break;
		}
	}
}
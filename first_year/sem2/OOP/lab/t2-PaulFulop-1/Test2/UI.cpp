#include "UI.h"

void UI::PrintCommands()
{
	std::cout << "Commands:\n1 -> add a new car\n2 -> show all cars\n3 -> save to file all cars having a price less than a given value\n4 -> exit\n";
}

void UI::InitData()
{
	serv.addCar(2, "Electric", 2);
	serv.addCar(4, "Electric", 1);
	serv.addCar(2, "Turbo", 2);
}

void UI::Start()
{
	InitData();
	PrintCommands();

	int cmd = 0;
	double price = 0;
	std::vector<Car> c;
	int numberOfDoors, autonomy = 0, n;
	std::string engineType;

	while (true)
	{
		std::cout << "\n> ";
		std::cin >> cmd;

		switch (cmd)
		{
		case 1:
			std::cout << "Insert the number of doors here: ";
			std::cin >> numberOfDoors;

			std::cout << "Insert the engine type here: ";
			std::cin >> engineType;

			if (engineType == "Electric")
			{
				std::cout << "Insert the autonomy here: ";
				std::cin >> autonomy;
			}

			serv.addCar(numberOfDoors, engineType, autonomy);
			c = serv.getAllCars();
			n = c.size();
			std::cout << "Added -> " << c[n - 1].toString() << '\n';
			break;
		case 2:
			c = serv.getAllCars();
			for (auto& car : c)
				std::cout << car.toString() << '\n';
			break;
		case 3:
			std::cout << "Read the max price here: ";
			std::cin >> price;
			c = serv.getCarsWithMaxPrice(price);
			serv.writeToFile("cars.txt", c);
			std::cout << "Wrote to file.\n";
			break;
		case 4:
			std::cout << "Exiting...\n\n";
			exit(0);
			break;
		default:
			std::cout << "Invalid command";
			break;
		}
	}
}
#include "UserInterface.h"
#include <iostream>


void UserInterface::DisplayMenuCommands() const
{
	cout << "1 -> Add a new car\n2 -> Remove a car\n3 -> Show all cars sorted by manufacturer name and model\n4 -> Show all vintage cars sorted by color\n5 -> Exit\n";
}

void UserInterface::StartMenu()
{
	DisplayMenuCommands();
	int cmd = 0;

	while (true)
	{
		cout << "\n> ";
		cin >> cmd;

		switch (cmd)
		{
		case 1:
			try {
				Car newCar = Car();
				cout << "Insert the manufacturer name: ";
				cin >> newCar.name;

				cout << "Insert the model: ";
				cin >> newCar.model;

				cout << "Insert the year: ";
				cin >> newCar.year;

				cout << "Insert the color: ";
				cin >> newCar.color;

				if (!newCar.ValidCar())
					throw exception("Invalid car.\n");

				serv.AddCar(newCar);
			}
			catch (const exception& e) {
				cout << e.what();
			}
			break;
		case 2:
			try {
				Car car = Car();
				cout << "Insert the model: ";
				cin >> car.model;

				cout << "Insert the year: ";
				cin >> car.year;

				serv.RemoveCar(car);
			}
			catch (const exception& e) {
				cout << e.what();
			}
			break;
		case 3:
			try {
				serv.SortCarsByManufacturerModel(serv.repo);
				cout << serv.ListCars(serv.repo);
			}
			catch (const exception& e) {
				cout << e.what();
			}
			break;
		case 4:
			try {
				Repository repo = serv.FilterVintageCars();
				serv.SortCarsByColor(repo);
				cout << serv.ListCars(repo);
			}
			catch (const exception& e) {
				cout << e.what();
			}
			break;
		case 5:
			cout << "Exiting...\n";
			exit(0);
			break;

		default:
			cout << "Invalid command.\n";
			break;
		}
	}
}
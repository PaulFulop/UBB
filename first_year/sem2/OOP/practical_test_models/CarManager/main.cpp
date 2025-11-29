#include "UserInterface.h"
#include <assert.h>

void Tests()
{
	Repository repo = Repository();
	assert(repo.AddCar(Car("n1", "m1", 2000, "c1")) == true);
	assert(repo.AddCar(Car("n1", "m1", 2000, "c1")) == false);
	assert(repo.AddCar(Car("n2", "m1", 2000, "c1")) == true);
	assert(repo.cars.size() == 2);

	Service serv = Service();

	serv.AddCar(Car("n3", "m3", 1900, "c3"));
	serv.AddCar(Car("n2", "m2", 1900, "c2"));
	serv.AddCar(Car("n1", "m1", 2020, "c1"));

	repo = serv.FilterVintageCars();
	serv.SortCarsByColor(repo);

	assert(repo.cars.size() == 2);
	assert(repo.cars[0].color == "c2");
}

int main()
{
	UserInterface ui = UserInterface();
	ui.serv.AddCar(Car("Fiat", "Bravo", 2007, "red"));
	ui.serv.AddCar(Car("Fiat", "Idea", 2003, "black"));
	ui.serv.AddCar(Car("Audi", "A5", 2007, "blue"));
	ui.serv.AddCar(Car("BMV", "Coupe", 2013, "pink"));
	ui.serv.AddCar(Car("Ford", "Fiesta", 1976, "yellow"));
	ui.StartMenu();

	Tests();
	return 0;
}
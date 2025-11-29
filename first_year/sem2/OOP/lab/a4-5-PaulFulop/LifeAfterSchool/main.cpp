#define _CRTDBG_MAP_ALLOC
#include "UserInterface.h"
#include "Tests.h"

void Run();
void AddEvents(UserInterface& ui);

int main()
{
	Run();
	_CrtDumpMemoryLeaks();
	return 0;
}

void Run()
{
	UserInterface ui = UserInterface();
	AddEvents(ui);

	ui.Start();
	TestAll();
}

void AddEvents(UserInterface& ui)			
{
	ui.adminServ.AddEvent(Event("title1", "desc1", "03/22/2025", 102, "https://github.com/cs-ubbcluj-ro/a4-5-PaulFulop"));
	ui.adminServ.AddEvent(Event("title2", "desc2", "03/30/2022", 1203, "https://github.com/cs-ubbcluj-ro/a4-5-PaulFulop"));
	ui.adminServ.AddEvent(Event("title3", "desc3", "04/17/2024", 52, "https://github.com/cs-ubbcluj-ro/a4-5-PaulFulop"));
	ui.adminServ.AddEvent(Event("title4", "desc4", "08/22/2020", 50000, "https://github.com/cs-ubbcluj-ro/a4-5-PaulFulop"));
	ui.adminServ.AddEvent(Event("title5", "desc5", "10/13/2025", 402145, "https://github.com/cs-ubbcluj-ro/a4-5-PaulFulop"));
	ui.adminServ.AddEvent(Event("title6", "desc6", "01/17/2018", 219844, "https://github.com/cs-ubbcluj-ro/a4-5-PaulFulop"));
	ui.adminServ.AddEvent(Event("title7", "desc7", "11/1/2023", 21055952, "https://github.com/cs-ubbcluj-ro/a4-5-PaulFulop"));
	ui.adminServ.AddEvent(Event("title8", "desc8", "02/9/2023", 123124, "https://github.com/cs-ubbcluj-ro/a4-5-PaulFulop"));
	ui.adminServ.AddEvent(Event("title9", "desc9", "02/27/2025", 3123, "https://github.com/cs-ubbcluj-ro/a4-5-PaulFulop"));
	ui.adminServ.AddEvent(Event("title10", "desc10", "01/26/2025", 11122, "https://github.com/cs-ubbcluj-ro/a4-5-PaulFulop"));
}
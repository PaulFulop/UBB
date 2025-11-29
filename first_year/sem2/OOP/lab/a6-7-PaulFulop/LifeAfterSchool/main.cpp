#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "UserInterface.h"
#include "Tests.h"

void Run();

int main()
{
	Run();
	_CrtDumpMemoryLeaks();
	return 0;
}

void Run()
{
	UserInterface ui = UserInterface({"events.txt", "user_events.txt", "user_events.csv", "user_events.html"});
	ui.Start();  
	TestAll();
}
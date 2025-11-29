#pragma once
#include "ServiceAM.h"
#include "ServiceUM.h"

class UserInterface {
public:
	ServiceAM adminServ;
	ServiceUM userServ;

	UserInterface();
	bool Mode();
	void PrintAdminMenu();
	void PrintUserMenu();
	void PrintUserCommands();
	void RunAdminMenu();
	void RunUserMenu();
	void Start();
};
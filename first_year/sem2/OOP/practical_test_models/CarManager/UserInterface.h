#pragma once
#include "Service.h"

class UserInterface {
public:
	Service serv;

	void DisplayMenuCommands() const;
	void StartMenu();
};
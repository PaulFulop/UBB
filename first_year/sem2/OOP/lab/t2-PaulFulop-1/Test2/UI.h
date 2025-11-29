#pragma once
#include "Service.h"
#include <iostream>

class UI {
private:
	Service serv;
public:
	void PrintCommands();
	void InitData();
	void Start();
};
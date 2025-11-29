#pragma once
#include "Service.h"


class UI {
private:
	Service serv;
public:
	void InitData();
	void PrintCommands();
	void Start();
};
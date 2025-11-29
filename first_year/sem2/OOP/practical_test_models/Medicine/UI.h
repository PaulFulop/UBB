#pragma once
#include "Person.h"
#include "BP.h"
#include "BMI.h"
#include <iostream>

class UI {
private:
	Person person;
public:
	void InitData();
	void PrintCommands();
	void Start();
};
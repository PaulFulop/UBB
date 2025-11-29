#pragma once
#include "service.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>

typedef struct {
	Service* serv;
}UI;

UI* CreateUI();
void Start(UI* ui);
void PrintMenu();
void PrintOptionsA();
char* EstateToStr(Estate* estate, char* buffer);
void DestroyUI(UI* ui);
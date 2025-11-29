#define _CRT_SECURE_NO_WARNINGS
#include "estate.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

Estate* NewEstate(char* type, char* address, int surface, int price)
{
	Estate *new_estate = (Estate*)malloc(sizeof(Estate));
	if (new_estate == NULL)
		return NULL;

	new_estate->type = (char*)malloc(sizeof(char) * (strlen(type) + 1));
	if (new_estate->type == NULL)
	{
		free(new_estate);
		return NULL;
	}

	new_estate->address = (char*)malloc(sizeof(char) * (strlen(address) + 1));
	if (new_estate->address == NULL)
	{
		free(new_estate->type);
		free(new_estate);
		return NULL;
	}

	strcpy(new_estate->type, type);
	strcpy(new_estate->address, address);
	new_estate->surface = surface;
	new_estate->price = price;

	return new_estate;
}

int ValidEstate(Estate* estate)
{
	if (strcmp(estate->type, "house") && strcmp(estate->type, "apartment") && strcmp(estate->type, "penthouse")) return 1;
	if (estate->price <= 0) return 2;
	if (estate->surface <= 0) return 3;
	return 0;
}

void DestroyEstate(Estate* estate)
{
	if (estate == NULL)
		return;

	free(estate->type);
	free(estate->address);
	free(estate);
}
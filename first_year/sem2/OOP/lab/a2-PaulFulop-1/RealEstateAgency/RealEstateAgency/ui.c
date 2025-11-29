#define _CRT_SECURE_NO_WARNINGS
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>

UI* CreateUI()
{
	UI* ui = (UI*)malloc(sizeof(UI));
	if (ui == NULL)
		return NULL;

	ui->serv = CreateService();

	return ui;
}

void Start(UI* ui)
{
	char cmd;
	char* text = malloc(500);
	strcpy(text, "");

	while (1)
	{
		system("cls");
		PrintMenu();
		printf("%s", text);
		printf("> ");
		scanf("%c", &cmd);

		if (getchar() != '\n')
			strcpy(text, "Invalid command.\n\n");
		else if (cmd == 'a')
		{
			int option = 7;
			char* text1 = malloc(500);
			strcpy(text1, "");
			strcpy(text, "");
			while (1)
			{
				system("cls");
				PrintOptionsA();
				printf("%s", text1);
				printf("Choose option: ");
				scanf("%d", &option);

				if(getchar() != '\n')
					strcpy(text1, "Invalid option.\n\n");
				else if (option == 1)
				{
					char *type = malloc(11), *address = malloc(50);
					int surface = -1, price = -1;

					printf("Insert the type here: ");
					scanf("%s", type);
					while (getchar() != '\n');

					if (strcmp(type, "house") && strcmp(type, "apartment") && strcmp(type, "penthouse"))
					{
						strcpy(text1, "Invalid type.\n\n");
						free(type);
						free(address);
						continue;
					}

					printf("Insert the address here: ");
					scanf("%s", address);
					while (getchar() != '\n');

					printf("Insert the surface here: ");
					scanf("%d", &surface);
					while (getchar() != '\n');

					if (surface <= 0)
					{
						strcpy(text1, "Invalid surface.\n\n");
						free(type);
						free(address);
						continue;
					}

					printf("Insert the price here: ");
					scanf("%d", &price);
					while (getchar() != '\n');

					if (price <= 0)
					{
						strcpy(text1, "Invalid price.\n\n");
						free(type);
						free(address);
						continue;
					}

					Repository* estates_with_address = FindEstates(ui->serv, address);
					if (estates_with_address->length)
						strcpy(text1, "There's an estate with that address.\n\n");
					else
					{
						Estate* new_estate = NewEstate(type, address, surface, price);
						AddUndoOperation(ui->serv);
						AddEstate(ui->serv, new_estate);
						strcpy(text1, "The new estate has been added successfully.\n\n");
						DestroyEstate(new_estate);
					}

					DestroyRepository(estates_with_address);
					free(type);
					free(address);
				}
				else if (option == 2)
				{
					char* address = malloc(50);
					printf("Insert the address here: ");
					scanf("%s", address);

					Repository* estates_with_address = FindEstates(ui->serv, address);

					if (!estates_with_address->length)
						strcpy(text1, "There is no estate with this address.\n\n");
					else
					{
						AddUndoOperation(ui->serv);
						DeleteEstate(ui->serv, address);
						strcpy(text1, "The estate has been removed successfully.\n\n");
					}

					DestroyRepository(estates_with_address);
					free(address);
				}
				else if (option == 3)
				{
					char *type = malloc(11), *address = malloc(50);
					int surface = -1, price = -1;

					printf("Insert the address of the estate you want updated here: ");
					scanf("%s", address);
					while (getchar() != '\n');

					Repository* estates_with_address = FindEstates(ui->serv, address);
					if (!estates_with_address->length)
					{
						strcpy(text1, "There is no estate with this address.\n\n");
						DestroyRepository(estates_with_address);
						free(type);
						free(address);
						continue;
					}

					DestroyRepository(estates_with_address);

					printf("Insert the new type here: ");
					scanf("%s", type);
					while (getchar() != '\n');

					if (strcmp(type, "house") && strcmp(type, "apartment") && strcmp(type, "penthouse"))
					{
						strcpy(text1, "Invalid type.\n\n");
						free(type);
						free(address);
						continue;
					}

					printf("Insert the new surface here: ");
					scanf("%d", &surface);
					while (getchar() != '\n');

					if (surface <= 0)
					{
						strcpy(text1, "Invalid surface.\n\n");
						free(type);
						free(address);
						continue;
					}

					printf("Insert the new price here: ");
					scanf("%d", &price);
					while (getchar() != '\n');

					if (price <= 0)
					{
						strcpy(text1, "Invalid price.\n\n");
						free(type);
						free(address);
						continue;
					}

					AddUndoOperation(ui->serv);
					UpdateEstate(ui->serv, type, address, surface, price);
					strcpy(text1, "Estate updated successfully.\n\n");

					free(type);
					free(address);
				}
				else if (option == 4)
				{
					bool success = Undo(ui->serv);
					if(success)
						strcpy(text1, "The last operation has been undone.\n\n");
					else
						strcpy(text1, "No more previous operations. Cannot undo anymore.\n\n");
				}
				else if (option == 5)
				{
					bool success = Redo(ui->serv);
					if (success)
						strcpy(text1, "The last operation has been performed again.\n\n");
					else
						strcpy(text1, "No more undos. Cannot redo anymore.\n\n");
				}
				else if (option == 6)
				{
					int v1;
					printf("Insert the value here: ");
					scanf("%d", &v1);

					AddUndoOperation(ui->serv);

					for (int i = 0; i < ui->serv->repo->length; ++i)
						if(ui->serv->repo->data[i]->price < v1)
							DeleteEstate(ui->serv, ui->serv->repo->data[i]->address), --i;
					
					strcpy(text1, "Estates were deleted.\n\n");
				}
				else if(option == 7)
					break;
				else
				{
					strcpy(text1, "Invalid option.\n\n");
					while (getchar() != '\n');
				}
			}

			free(text1);
		}
		else if (cmd == 'b')
		{
			char* filter = malloc(50);
			printf("Insert a filter here: ");
			fgets(filter, 50, stdin);


			if (filter[0] == '\n')
				strcpy(filter, "");
			else
				filter[strlen(filter) - 1] = '\0';

			Repository* filtered_estates = FindEstates(ui->serv, filter);
			SortEstatesByPrice(filtered_estates);

			if (!filtered_estates->length)
				strcpy(text, "No estates found.\n\n");
			else
			{
				strcpy(text, "");
				char* buffer = malloc(100);
				for (int i = 0; i < filtered_estates->length; ++i)
					strcat(text, EstateToStr(filtered_estates->data[i], buffer));
				strcat(text, "\n");
				free(buffer);
			}

			DestroyRepository(filtered_estates);
			free(filter);
		}
		else if (cmd == 'c')
		{
			char* type_filter = malloc(11);
			int surface_filter = -1;

			printf("Insert the type of the estates you want to see here: ");
			scanf("%s", type_filter);

			printf("Insert the minimum surface of a desired estate: ");
			scanf("%d", &surface_filter);

			if (strcmp(type_filter, "house") && strcmp(type_filter, "apartment") && strcmp(type_filter, "penthouse"))
				strcpy(text, "Invalid estate type.\n\n");
			else if (surface_filter <= 0)
				strcpy(text, "Invalid surface.\n\n");
			else
			{
				Repository* filtered_estates = GetCustomEstates(ui->serv, type_filter, surface_filter);

				if (!filtered_estates->length)
					strcpy(text, "No estates found.\n");
				else
				{
					char* buffer = malloc(100);
					strcpy(text, "");
					for (int i = 0; i < filtered_estates->length; ++i)
						strcat(text, EstateToStr(filtered_estates->data[i], buffer));
					strcat(text, "\n");
					free(buffer);
				}

				DestroyRepository(filtered_estates);
			}

			free(type_filter);
			while (getchar() != '\n');
		}
		else if (cmd == 'd')
		{
			char* type_filter = malloc(11);
			int surface_filter = -1;

			printf("Insert the type of the estates you want to see here: ");
			scanf("%s", type_filter);

			printf("Insert the minimum surface of a desired estate: ");
			scanf("%d", &surface_filter);

			if (strcmp(type_filter, "house") && strcmp(type_filter, "apartment") && strcmp(type_filter, "penthouse"))
				strcpy(text, "Invalid estate type.\n\n");
			else if (surface_filter <= 0)
				strcpy(text, "Invalid surface.\n\n");
			else
			{
				Repository* filtered_estates = GetCustomEstates(ui->serv, type_filter, surface_filter);

				if (!filtered_estates->length)
					strcpy(text, "No estates found.\n");
				else
				{
					SortEstatesBySurface(filtered_estates);
					char* buffer = malloc(100);
					strcpy(text, "");
					for (int i = 0; i < filtered_estates->length; ++i)
						strcat(text, EstateToStr(filtered_estates->data[i], buffer));
					strcat(text, "\n");
					free(buffer);
				}

				DestroyRepository(filtered_estates);
			}

			free(type_filter);
			while (getchar() != '\n');
		}
		else if (cmd == 'e')
		{
			printf("Exiting...\n\n");
			break;
		}
		else
			strcpy(text, "Invalid command.\n\n");
	}

	free(text);
}

void DestroyUI(UI* ui)
{
	if (ui == NULL)
		return;

	DestroyService(ui->serv);
	free(ui);
}

void PrintMenu()
{
	char* o1 = " a -> manage estates.\n";
	char* o2 = " b -> display all estates whose address contains a given string (sorted ascending by their price).\n";
	char* o3 = " c -> see all estates of a given type, having the surface greater than a user provided value.\n";
	char* o4 = " d -> the functionality in c, but sorted in ascending order by surface.\n";
	char* o5 = " e -> exit.\n\n";

	printf("\nReal Estate Agency Menu:\n\n%s%s%s%s%s", o1, o2, o3, o4, o5);
}

void PrintOptionsA()
{
	printf(" 1 -> add new estate.\n 2 -> remove an estate.\n 3 -> update an estate.\n 4 -> undo.\n 5 -> redo.\n 6 -> remove estates that have the price smaller than a user provided value\n 7 -> close.\n\n");
}

char* EstateToStr(Estate* estate, char* buffer)
{
	sprintf(buffer, "%s, %s, %d, %d\n", estate->type, estate->address, estate->surface, estate->price);
	return buffer;
}
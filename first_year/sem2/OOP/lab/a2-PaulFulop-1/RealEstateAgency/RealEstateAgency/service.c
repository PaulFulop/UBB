#define _CRT_SECURE_NO_WARNINGS
#include "service.h"
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>

Service* CreateService()
{
	Service* serv = (Service*)malloc(sizeof(Service));
	if (serv == NULL)
		return NULL;

	serv->repo = CreateRepository(1);
	serv->undo_history = CreateOperationStack(1);
	serv->redo_history = CreateOperationStack(1);

	return serv;
}

void AddEstate(Service* serv, Estate* estate)
{
	AddToRepo(serv->repo, estate);
}

void DeleteEstate(Service* serv, char* address)
{
	int i;
	for (i = 0; i < serv->repo->length; ++i)
		if (!strcmp(address, serv->repo->data[i]->address))
			break;

	RemoveFromRepo(serv->repo, i);
}

void UpdateEstate(Service* serv, char* type, char* address, int surface, int price)
{
	int i;
	for (i = 0; i < serv->repo->length; ++i)
		if (!strcmp(address, serv->repo->data[i]->address))
			break;

	UpdateToRepo(serv->repo, i, type, address, surface, price);
}

Repository* FindEstates(Service* serv, char* filter)
{
	Repository* repo = CreateRepository(serv->repo->length);
	for (int i = 0; i < serv->repo->length; ++i)
		if (strstr(serv->repo->data[i]->address, filter) != NULL)
			AddToRepo(repo, serv->repo->data[i]);

	return repo;
}

Repository* GetCustomEstates(Service* serv, char* type_filter, int surface_filter)
{
	Repository* repo = CreateRepository(1);
	for (int i = 0; i < serv->repo->length; ++i)
		if (!strcmp(type_filter, serv->repo->data[i]->type) && serv->repo->data[i]->surface > surface_filter)
			AddToRepo(repo, serv->repo->data[i]);

	return repo;
}

void AddUndoOperation(Service* serv)
{
	Add(serv->undo_history, serv->repo);
}

void AddRedoOperation(Service* serv)
{ 
	Add(serv->redo_history, serv->repo);
}

bool Undo(Service* serv)
{
	if (!serv->undo_history->length)
		return false;

	AddRedoOperation(serv);

	DestroyRepository(serv->repo);
	serv->repo = Pop(serv->undo_history);

	return true;
}

bool Redo(Service* serv)
{
	if (!serv->redo_history->length)
		return false;

	AddUndoOperation(serv);
	DestroyRepository(serv->repo);
	serv->repo = Pop(serv->redo_history);

	return true;
}

void DestroyService(Service* serv)
{
	if (serv == NULL)
		return;

	DestroyRepository(serv->repo);
	DestroyOperationStack(serv->undo_history);
	DestroyOperationStack(serv->redo_history);
	free(serv);
}

void SortEstatesByPrice(Repository* repo)
{
	char* temp_type = malloc(11);
	char* temp_address = malloc(50);
	int temp_surface, temp_price;

	for (int i = 0; i < repo->length - 1; ++i)
		for (int j = i + 1; j < repo->length; ++j)
			if (repo->data[i]->price > repo->data[j]->price)
			{
				strcpy(temp_type, repo->data[i]->type);
				strcpy(temp_address, repo->data[i]->address);
				temp_surface = repo->data[i]->surface;
				temp_price = repo->data[i]->price;

				UpdateToRepo(repo, i, repo->data[j]->type, repo->data[j]->address, repo->data[j]->surface, repo->data[j]->price);
				UpdateToRepo(repo, j, temp_type, temp_address, temp_surface, temp_price);
			}

	free(temp_type);
	free(temp_address);
}

void SortEstatesBySurface(Repository* repo)
{
	char* temp_type = malloc(11);
	char* temp_address = malloc(50);
	int temp_surface, temp_price;

	for (int i = 0; i < repo->length - 1; ++i)
		for (int j = i + 1; j < repo->length; ++j)
			if (repo->data[i]->surface > repo->data[j]->surface)
			{
				strcpy(temp_type, repo->data[i]->type);
				strcpy(temp_address, repo->data[i]->address);
				temp_surface = repo->data[i]->surface;
				temp_price = repo->data[i]->price;

				UpdateToRepo(repo, i, repo->data[j]->type, repo->data[j]->address, repo->data[j]->surface, repo->data[j]->price);
				UpdateToRepo(repo, j, temp_type, temp_address, temp_surface, temp_price);
			}

	free(temp_type);
	free(temp_address);
}
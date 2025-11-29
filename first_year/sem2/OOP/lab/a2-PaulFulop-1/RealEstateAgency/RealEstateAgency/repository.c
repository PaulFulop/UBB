#define _CRT_SECURE_NO_WARNINGS
#include "repository.h"
#include <stdlib.h>

Repository* CreateRepository(int capacity)
{
	Repository* repo = (Repository*)malloc(sizeof(Repository));
	if (repo == NULL)
		return NULL;

	repo->data = malloc(capacity * sizeof(Estate*));

	if (repo->data == NULL)
	{
		free(repo);
		return NULL;
	}

	repo->capacity = capacity;
	repo->length = 0;
	return repo;
}

void AddToRepo(Repository* repo, Estate* new_estate)
{
	if (repo == NULL || repo->data == NULL)
		return;

	if (repo->length == repo->capacity)
		Resize(repo);
	
	repo->data[repo->length++] = NewEstate(new_estate->type, new_estate->address, new_estate->surface, new_estate->price);
}

void Resize(Repository* repo)
{
	if (repo == NULL || repo->data == NULL)
		return;

	repo->capacity *= 2;
	Estate** aux = realloc(repo->data, repo->capacity * sizeof(Estate*));

	if (aux == NULL)
		return;

	repo->data = aux;
}

void RemoveFromRepo(Repository* repo, int pos)
{
	if (repo == NULL)
		return;

	for (int i = pos; i < repo->length - 1; ++i)
		UpdateToRepo(repo, i, repo->data[i + 1]->type, repo->data[i + 1]->address, repo->data[i + 1]->surface, repo->data[i + 1]->price);

	--repo->length;
	DestroyEstate(repo->data[repo->length]);
}

void UpdateToRepo(Repository* repo, int pos, char* new_type, char* new_address, int new_surface, int new_price)
{
	char* aux = realloc(repo->data[pos]->type, strlen(new_type) + 1);
	if (aux == NULL)
		return;

	repo->data[pos]->type = aux;
	strcpy(repo->data[pos]->type, aux);

	aux = realloc(repo->data[pos]->address, strlen(new_address) + 1);
	if (aux == NULL)
		return;

	repo->data[pos]->address = aux;

	strcpy(repo->data[pos]->type, new_type);
	strcpy(repo->data[pos]->address, new_address);
	repo->data[pos]->surface = new_surface;
	repo->data[pos]->price = new_price;
}

void DestroyRepository(Repository* repo)
{
	if (repo == NULL)
		return;

	for(int i = 0; i < repo->length; ++i)
		DestroyEstate(repo->data[i]);

	free(repo->data);
	free(repo);
}
#define _CRT_SECURE_NO_WARNINGS
#include "tests.h"
#include <crtdbg.h>
#include <string.h>

void TestEstate()
{
	Estate* estate = NewEstate("penthouse", "test_str", 100, 200);

	assert(!strcmp(estate->type, "penthouse"));
	assert(!strcmp(estate->address, "test_str"));
	assert(estate->surface == 100);
	assert(estate->price == 200);

	assert(ValidEstate(estate) == 0);
	DestroyEstate(estate);
}

void TestRepo()
{
	Repository* repo = CreateRepository(1);

	assert(repo->capacity == 1);
	assert(repo->length == 0);

	Estate* est1 = NewEstate("house", "str1", 50, 10000);
	Estate* est2 = NewEstate("apartment", "str2", 60, 1234);

	AddToRepo(repo, est1);
	AddToRepo(repo, est2);

	assert(repo->capacity == 2);
	assert(repo->length == 2);
	assert(!strcmp(repo->data[0]->type, "house"));
	assert(!strcmp(repo->data[0]->address, "str1"));
	assert(repo->data[0]->surface == 50);
	assert(repo->data[0]->price == 10000);

	RemoveFromRepo(repo, 1);
	assert(repo->length == 1);

	UpdateToRepo(repo, 0, "penthouse", "str3", 500, 20000);

	assert(!strcmp(repo->data[0]->type, "penthouse"));
	assert(!strcmp(repo->data[0]->address, "str3"));
	assert(repo->data[0]->surface == 500);
	assert(repo->data[0]->price == 20000);

	DestroyRepository(repo);
	DestroyEstate(est1);
	DestroyEstate(est2);
}

void TestOperationStack()
{
	OperationStack* os = CreateOperationStack(1);

	assert(os->capacity == 1);
	assert(os->length == 0);

	Repository* repo = CreateRepository(1);

	Estate* est1 = NewEstate("house", "str1", 50, 10000);
	Estate* est2 = NewEstate("apartment", "str2", 60, 1234);

	AddToRepo(repo, est1);
	AddToRepo(repo, est2);

	Add(os, repo);

	assert(os->length == 1);

	Repository* repo1 = Pop(os);

	assert(repo1->length == 2);
	assert(os->length == 0);

	DestroyRepository(repo1);
	DestroyRepository(repo);
	DestroyEstate(est1);
	DestroyEstate(est2);
	DestroyOperationStack(os);
}

void TestService()
{
	Service* serv = CreateService();

	assert(serv->repo->capacity == 1);
	assert(serv->undo_history->capacity == 1);
	assert(serv->redo_history->capacity == 1);

	Estate* est1 = NewEstate("house", "str1", 50, 10000);
	Estate* est2 = NewEstate("apartment", "str2", 60, 1234);
	AddEstate(serv, est1);
	AddEstate(serv, est2);

	assert(serv->repo->length == 2);

	DeleteEstate(serv, "str1");

	assert(serv->repo->length == 1);

	UpdateEstate(serv, "penthouse", "str2", 70, 12345);

	assert(!strcmp(serv->repo->data[0]->type, "penthouse"));
	assert(serv->repo->data[0]->surface == 70);
	assert(serv->repo->data[0]->price == 12345);
	
	Repository* found_estates = FindEstates(serv, "str");

	assert(found_estates->length == 1);

	DestroyRepository(found_estates);

	found_estates = GetCustomEstates(serv, "penthouse", 10);

	assert(found_estates->length == 1);

	DestroyRepository(found_estates);

	AddUndoOperation(serv);
	AddRedoOperation(serv);

	assert(serv->undo_history->length == 1);
	assert(serv->redo_history->length == 1);

	assert(Undo(serv) == true);
	assert(Undo(serv) == false);
	assert(Redo(serv) == true);
	assert(Redo(serv) == true);
	assert(Redo(serv) == false);

	AddEstate(serv, est1);

	SortEstatesByPrice(serv->repo);
	assert(serv->repo->data[0]->price == 10000);
	assert(serv->repo->data[1]->price == 12345);

	SortEstatesBySurface(serv->repo);
	assert(serv->repo->data[0]->surface == 50);
	assert(serv->repo->data[1]->surface == 70);

	DestroyEstate(est1);
	DestroyEstate(est2);
	DestroyService(serv);
}
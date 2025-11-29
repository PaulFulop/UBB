#include <stdlib.h>
#include "operation_stack.h"

OperationStack* CreateOperationStack(int capacity)
{
	OperationStack* os = malloc(sizeof(OperationStack));

	if (os == NULL)
		return NULL;

	os->history = malloc(capacity * sizeof(Repository*));

	if (os->history == NULL)
	{
		free(os);
		return NULL;
	}

	os->capacity = capacity;
	os->length = 0;
}

void Add(OperationStack* os, Repository* state)
{
	if (os == NULL || os->history == NULL)
		return;

	if (os->length == os->capacity)
		ResizeOS(os);

	os->history[os->length] = CreateRepository(state->capacity);

	for (int i = 0; i < state->length; ++i)
		AddToRepo(os->history[os->length], state->data[i]);

	++os->length;
}

void ResizeOS(OperationStack* os)
{
	if (os == NULL || os->history == NULL)
		return;

	os->capacity *= 2;
	Repository** aux = realloc(os->history, os->capacity * sizeof(Repository*));

	if (aux == NULL)
		return;

	os->history = aux;
}

Repository* Pop(OperationStack* os)
{
	if (!os->length)
		return CreateRepository(1);

	return os->history[--os->length];
}

void DestroyOperationStack(OperationStack* os)
{
	if (os == NULL)
		return;

	for (int i = 0; i < os->length; ++i)
		DestroyRepository(os->history[i]);
	free(os->history);
	free(os);
}
#pragma once
#include "repository.h"

typedef struct {
	Repository** history;
	int length, capacity;
}OperationStack;

/**
 * @brief Creates a Operation Stack object.
 * 
 * @param capacity Capacity allocated for the history field.
 * @return OperationStack* 
 */
OperationStack* CreateOperationStack(int capacity);

/**
 * @brief Adds a new state (how the data stored in the repository looks like) to the operation stack.
 * 
 * @param os Pointer to the operation stack object to add the repository to.
 * @param state Pointer to the repository object that has to be added to the operation stack.
 */
void Add(OperationStack* os, Repository* state);

/**
 * @brief Resizes the operation stack in case the capacity is exceeded.
 * 
 * @param os Pointer to the operation stack object that has to be resized.
 */
void ResizeOS(OperationStack* os);

/**
 * @brief Removes the last repository object from the operation stack and returns it.
 * 
 * @param os Pointer to the operation stack object from which data is taken.
 * @return Repository* 
 */
Repository* Pop(OperationStack* os);

/**
 * @brief Destroys the memory allocated for the operation stack.
 * 
 * @param os Pointer to the operation stack object to destroy.
 */
void DestroyOperationStack(OperationStack* os);
#pragma once
#include "estate.h"
#include <string.h>

typedef struct {
	Estate** data;
	int length, capacity;
} Repository;

/**
 * @brief Creates a Repository object.
 * 
 * @param capacity Capacity allocated for the data field.
 * @return Repository* 
 */
Repository *CreateRepository(int capacity);

/**
 * @brief Adds a new estate on the repository.
 * 
 * @param repo Pointer to the repository object.
 * @param new_estate Pointer to the new estate to add.
 */
void AddToRepo(Repository* repo, Estate* new_estate);

/**
 * @brief Resizes the repository in case the capacity is exceeded.
 * 
 * @param repo Pointer to the repository object that has to be resized.
 */
void Resize(Repository* repo);

/**
 * @brief Removes an estate object from the repo, at position pos.
 * 
 * @param repo Pointer to the repository object.
 * @param pos Position of the estate to delete.
 */
void RemoveFromRepo(Repository* repo, int pos);

/**
 * @brief Updates an estate object from the repo, at position pos.
 * 
 * @param repo Pointer to the repository object.
 * @param pos Position of the estate to update.
 * @param new_type The new type of the estate.
 * @param new_address The new address of the estate.
 * @param new_surface The new surface of the estate.
 * @param new_price The new price of the estate.
 */
void UpdateToRepo(Repository* repo, int pos, char* new_type, char* new_address, int new_surface, int new_price);

/**
 * @brief Destroys the memory allocated for the repository.
 * 
 * @param repo Pointer to the repository object to destroy.
 */
void DestroyRepository(Repository* repo);
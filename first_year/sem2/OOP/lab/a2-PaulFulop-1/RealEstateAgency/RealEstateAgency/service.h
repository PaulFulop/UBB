#pragma once
#include "operation_stack.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
	Repository* repo;
	OperationStack *undo_history, *redo_history;
}Service;

/**
 * @brief Create a Service object.
 * 
 * @return Service* 
 */
Service* CreateService();

/**
 * @brief Adds a new estate.
 * 
 * @param serv Pointer to the service object.
 * @param estate Pointer to the estate object to add.
 */
void AddEstate(Service* serv, Estate* estate);

/**
 * @brief Deletes an estate that has a certain address.
 * 
 * @param serv Pointer to the service object.
 * @param address Address of the estate to delete.
 */
void DeleteEstate(Service* serv, char* address);

/**
 * @brief Updates an estate that has a certain address.
 * 
 * @param serv Pointer to the service object.
 * @param type The new type of the estate.
 * @param address The address of the estate to update.
 * @param surface The new surface of the estate.
 * @param price The new price of the estate.
 */
void UpdateEstate(Service* serv, char* type, char* address, int surface, int price);

/**
 * @brief Finds all estates for which the address contains a given filter.
 * 
 * @param serv Pointer to the service object.
 * @param filter The address filter.
 * @return Repository* 
 */
Repository* FindEstates(Service *serv, char *filter);

/**
 * @brief Finds all estates of a given type, having the surface greater than a uer provided value.
 * 
 * @param serv Pointer to the service object.
 * @param type_filter The type of the estates to find.
 * @param surface_filter The surface of the filtered estates has to be greater than this value.
 * @return Repository* 
 */
Repository* GetCustomEstates(Service* serv, char* type_filter, int surface_filter);

/**
 * @brief Adds the current repository state of the service to the undo operation stack.
 * 
 * @param serv Pointer to the service object.
 */
void AddUndoOperation(Service* serv);

/**
 * @brief Adds the current repository state of the service to the redo operation stack.
 * 
 * @param serv Pointer to the service object.
 */
void AddRedoOperation(Service* serv);

/**
 * @brief Undo the last operation made.
 * 
 * @param serv Pointer to the service object.
 * @return true If there was at least one operation to undo.
 * @return false If there was no operation to undo.
 */
bool Undo(Service* serv);

/**
 * @brief Redo the last operation made.
 * 
 * @param serv Pointer to the service object.
 * @return true If there was at least one undo operation before this.
 * @return false If there was no undo operation before this.
 */
bool Redo(Service* serv);

/**
 * @brief Destroys the memory allocated for the service.
 * 
 * @param serv Pointer to the service object.
 */
void DestroyService(Service* serv);

/**
 * @brief Sorts the estates in the repository by their price.
 * 
 * @param repo Pointer to the repository object.
 */
void SortEstatesByPrice(Repository* repo);

/**
 * @brief Sorts the estates in the repository by their surface.
 * 
 * @param repo Pointer to the repository object.
 */
void SortEstatesBySurface(Repository* repo);
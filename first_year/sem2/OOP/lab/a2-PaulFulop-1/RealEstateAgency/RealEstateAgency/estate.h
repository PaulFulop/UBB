#pragma once

typedef struct {
	char *type, *address;
	int surface, price;
} Estate;

/**
 * @brief Creates a new estate.
 * 
 * @param type The type of the estate.
 * @param address The address of the estate (unique identifier).
 * @param surface The surface of the estate.
 * @param price The price of the estate.
 * @return Estate*
 */
Estate* NewEstate(char* type, char* address, int surface, int price);

/**
 * @brief Checks if a given estate is valid.
 * 
 * @param estate Pointer to the estate object to check validity for.
 * @return int 
 */
int ValidEstate(Estate* estate);

/**
 * @brief Destroys the memory allocated for the estate.
 * 
 * @param estate Pointer to the estate object to destroy.
 */
void DestroyEstate(Estate* estate);
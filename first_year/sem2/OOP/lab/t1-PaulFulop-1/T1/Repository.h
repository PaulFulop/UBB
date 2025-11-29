#pragma once
#include <vector>
#include "School.h"

class Repository {
public:
	vector<School> schools;

	Repository();

 /**
     @brief  Removes a school
     @param  name    - the name of the school
     @param  address - the address o the school
     @retval         - true if it has been found, false otherwise
 **/
	bool Remove(string name, pair<double, double> address);
	int Search(string name, pair<double, double> address);
	void Add(School new_school);
};
#pragma once
#include "Repository.h"

class Service {
public:
	Repository repo;

	Service();

	void RemoveSchool(string name, pair<double, double> address);
	string DisplaySchools();
	void SortByName(Repository& repo);

 /**
     @brief  Marks all schools that have a date before a given date as visited and returns a string with those that have a date after it and are visited
     @param  date - the user provided date
     @retval      - a string containing the said dates
 **/
	string MarkDisplaySchools(string date);
};
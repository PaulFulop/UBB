#include "School.h"

School::School(): name {""}, address {pair<double, double>(0, 0)}, date {""}, visited {false}
{ }

School::School(string _name, pair<double, double> _address, string _date, bool _visited) :name{ _name }, address{ _address }, date{ _date }, visited{ _visited }
{}

string School::toString() const
{
	string strVisited = "";

	if (visited)
		strVisited = "visited";
	else
		strVisited = "not visited";

	return name + " " + to_string(address.first) + " " + to_string(address.second) + " " + date + " " + strVisited;
}

int School::intYear()
{
	string yearStr = date.substr(0, 4);
	return stoi(yearStr);
}

int School::intMonth()
{
	string monthStr = date.substr(5, 2);
	return stoi(monthStr);
}

int School::intDay()
{
	string dayStr = date.substr(8, 2);
	return stoi(dayStr);
}

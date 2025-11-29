#pragma once
#include <string>
using namespace std;

class School {
public:
	string name;
	pair<double, double> address;
	string date;
	bool visited;

	School();
	School(string _name, pair<double, double> _address, string _date, bool _visited);
	string toString() const;
	int intYear();
	int intMonth();
	int intDay();
};
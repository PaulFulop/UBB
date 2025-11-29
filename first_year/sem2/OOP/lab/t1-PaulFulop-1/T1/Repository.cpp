#include "Repository.h"

Repository::Repository(): schools {vector<School>()}
{}

bool Repository::Remove(string name, pair<double, double> address)
{
	int pos = Search(name, address);
	if (pos == -1)
		return false;

	schools.erase(schools.begin() + pos);
	return true;
}

int Repository::Search(string name, pair<double, double> address)
{
	for (int i = 0; i < schools.size(); ++i)
		if (schools[i].name == name && schools[i].address.first == address.first && schools[i].address.second == address.second)
			return i;

	return -1;
}

void Repository::Add(School new_school)
{
	schools.push_back(new_school);
}
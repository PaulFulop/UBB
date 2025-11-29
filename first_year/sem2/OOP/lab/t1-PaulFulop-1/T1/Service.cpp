#include "Service.h"

Service::Service(): repo {Repository()}
{ }

void Service::RemoveSchool(string name, pair<double, double> address)
{
	if (repo.Remove(name, address) == false)
		throw exception("No such school has been found.\n");
}

string Service::DisplaySchools()
{
	string s = "\n";
	Repository new_repo = repo;

	SortByName(new_repo);

	for (int i = 0; i < repo.schools.size(); ++i)
		s += new_repo.schools[i].toString() + "\n";

	return s;
}

void Service::SortByName(Repository& repo)
{
	for (int i = 0; i < repo.schools.size() - 1; ++i)
		for (int j = i + 1; j < repo.schools.size(); ++j)
			if (repo.schools[i].name > repo.schools[j].name)
				swap(repo.schools[i], repo.schools[j]);
}

string Service::MarkDisplaySchools(string date)
{
	string s = "\n";
	int intYear = stoi(date.substr(0, 4));
	int intMonth = stoi(date.substr(5, 2));
	int intDay = stoi(date.substr(8, 2));

	for (int i = 0; i < repo.schools.size(); ++i)
	{
		if (intYear > repo.schools[i].intYear() ||
			(intYear == repo.schools[i].intYear() && intMonth > repo.schools[i].intMonth()) ||
			(intYear == repo.schools[i].intYear() && intMonth == repo.schools[i].intMonth() && intDay > repo.schools[i].intDay()))
			repo.schools[i].visited = true;
		else
			if(repo.schools[i].visited)
				s += repo.schools[i].toString() + "\n";
	}

	return s;
}

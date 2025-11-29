#pragma once
#include "Repo.h"
#include "Issue.h"
#include "User.h"

class Service{
public:
	User u;
	Repo<Issue>* issues;
	bool* sorted;


	Service() = default;
	Service(const User& u, Repo<Issue>* issues, bool* sorted)
		: u(u), issues(issues), sorted(sorted)
	{}

	void SortIssues();
	void AddIssue(std::string description);
	void ResolveIssue(Issue& issue) const;
	void RemoveIssue(const Issue& issue);
	bool IsTester() const;
	bool IsIssueOpen(const Issue& i) const;
};


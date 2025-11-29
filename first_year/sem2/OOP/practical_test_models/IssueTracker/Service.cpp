#include "Service.h"
#include <algorithm>

void Service::SortIssues() {
	if (sorted && *sorted == false) {
		std::sort(issues->data.begin(), issues->data.end(), [](const Issue& i1, const Issue& i2) {return (i1.status > i2.status) || (i1.status == i2.status && i1.desc < i2.desc); });
		*sorted = true;
	}
}

void Service::AddIssue(std::string description) {
	if (description == "") throw std::exception("Description is empty!");
	for (const auto& issue : issues->data)
		if (issue.desc == description) throw std::exception("There is a description like this already!");

	Issue newIssue = Issue(description, true, u.name, "");
	issues->Add(newIssue);
	*sorted = false;
}

void Service::ResolveIssue(Issue& issue) const {
	issue.solver = u.name;
}

void Service::RemoveIssue(const Issue& issue) {
	issues->data.erase(std::find(issues->data.begin(), issues->data.end(), issue));
}

bool Service::IsTester() const {
	return u.type == "tester";
}

bool Service::IsIssueOpen(const Issue& i) const {
	return i.status;
}
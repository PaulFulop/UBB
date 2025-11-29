#include "Service.h"
#include <algorithm>

bool Service::IsRevised(const SourceFile& f) {
	return f.status == "revised";
}

bool Service::CreatorOfFile(const SourceFile& f) const {
	return p->name == f.creator;
}

bool Service::RevisedAllFiles() const {
	return p->filesToRevise == 0;
}

void Service::SortFiles() {
	if (*sorted == false) {
		*sorted = true;
		std::sort(files->data.begin(), files->data.end(), [](const SourceFile& f1, const SourceFile& f2) {return f1.name < f2.name; });
	}
}

void Service::AddFile(const SourceFile& newF) {
	if (newF.name == "") throw std::exception("The file name is empty!");
	for (const auto& f : files->data)
		if (f.name == newF.name) throw std::exception("Duplicate file!");
	*sorted = false;
	files->Add(newF);
}

void Service::ReviseFile(SourceFile& f) {
	f.status = "revised";
	f.reviewer = p->name;
	++p->revisedFiles;
	--p->filesToRevise;
}
#pragma once
#include "Repo.h"
#include "Programmer.h"
#include "SourceFile.h"

class Service{
public:
	Programmer* p;
	Repo<SourceFile>* files;
	bool* sorted;

	bool IsRevised(const SourceFile& f);
	bool CreatorOfFile(const SourceFile& f) const;
	bool RevisedAllFiles() const;
	void SortFiles();
	void AddFile(const SourceFile& newF);
	void ReviseFile(SourceFile& f);

	Service() = default;
	Service(Programmer* p, Repo<SourceFile>* files, bool* sorted)
		: p(p), files(files), sorted(sorted){ }
};


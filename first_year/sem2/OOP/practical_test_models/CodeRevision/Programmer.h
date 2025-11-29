#pragma once
#include <string>

class Programmer{
public:
	std::string name;
	int revisedFiles, filesToRevise;

	Programmer() = default;
	Programmer(const std::string& name, int revisedFiles, int filesToRevise)
		: name(name), revisedFiles(revisedFiles), filesToRevise(filesToRevise)
	{}

	friend std::istream& operator >> (std::istream& is, Programmer& p);
	friend std::ostream& operator << (std::ostream& os, const Programmer& p);
};


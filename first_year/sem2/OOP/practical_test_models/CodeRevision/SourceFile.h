#pragma once
#include <string>

class SourceFile{
public:
	std::string name, status, creator, reviewer;

	SourceFile() = default;
	SourceFile(const std::string& name, const std::string& status, const std::string& creator, const std::string& reviewer)
		: name(name), status(status), creator(creator), reviewer(reviewer)
	{}

	friend std::istream& operator >> (std::istream& is, SourceFile& s);
	friend std::ostream& operator << (std::ostream& os, const SourceFile& s);
	std::string ToString() const;
};


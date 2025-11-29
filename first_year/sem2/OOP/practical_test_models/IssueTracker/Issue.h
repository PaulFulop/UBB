#pragma once
#include <string>

class Issue{
public:
	std::string desc;
	bool status;
	std::string reporter, solver;



	Issue() = default;

	Issue(const std::string& desc, bool status, const std::string& reporter, const std::string& solver)
		: desc(desc), status(status), reporter(reporter), solver(solver)
	{
	}

	friend std::istream& operator >> (std::istream& is, Issue& i);
	friend std::ostream& operator << (std::ostream& os, const Issue& i);
	bool operator == (const Issue& other) { return desc == other.desc; }

	std::string ToString() const;
};


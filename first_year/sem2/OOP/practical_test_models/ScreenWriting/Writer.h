#pragma once
#include <string>

class Writer{
public:
	std::string name, expertise;

	Writer() = default;
	Writer(const std::string& name, const std::string& expertise)
		: name(name), expertise(expertise)
	{}

	friend std::istream& operator >> (std::istream& is, Writer& w);
	friend std::ostream& operator << (std::ostream& os, const Writer& w);
};


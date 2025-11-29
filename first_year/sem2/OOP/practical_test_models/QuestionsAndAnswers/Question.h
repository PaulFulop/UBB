#pragma once
#include <string>
#include "Utils.h"

class Question{
public:
	int id;
	std::string text, name;

	Question() = default;

	Question(int id, const std::string& text, const std::string& name)
		: id(id), text(text), name(name)
	{
	}

	friend std::istream& operator >> (std::istream& is, Question& q);
	friend std::ostream& operator << (std::ostream& os, const Question& q);
	std::string ToString() const;
	int SimilarityScore(std::string attempt) const;
};


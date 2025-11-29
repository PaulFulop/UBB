#pragma once
#include <string>
#include "Utils.h"

class Answer{
public:
	int id = -1, qId;
	std::string name, text;
	int votes;

	Answer() = default;

	Answer(int id, int qId, const std::string& name, const std::string& text, int votes)
		: id(id), qId(qId), name(name), text(text), votes(votes)
	{
	}

	friend std::istream& operator >> (std::istream& is, Answer& a);
	friend std::ostream& operator << (std::ostream& os, const Answer& a);
	std::string ToString() const;
	void operator = (const Answer& a) {
		id = a.id;
		qId = a.qId;
		name = a.name;
		text = a.text;
		votes = a.votes;
	}
};


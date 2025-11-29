#pragma once
#include <string>

class Question {
public:
	int id, score;
	std::string text, answer;

	Question();
	Question(int _id, std::string _text, std::string _answer, int _score);
	std::string ToStringPresenter() const noexcept;
	std::string ToStringParticipant() const noexcept;
	friend std::istream& operator >> (std::istream& is, Question& q);
	friend std::ostream& operator << (std::ostream& os, const Question& q);
};

class Participant {
public:
	std::string name;
	int score;

	Participant();
	Participant(std::string _name, int _score = 0);
	friend std::istream& operator >> (std::istream& is, Participant& p);
	friend std::ostream& operator << (std::ostream& os, const Participant& p);
};
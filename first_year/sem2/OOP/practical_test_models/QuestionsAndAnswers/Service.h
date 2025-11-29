#pragma once
#include "Repo.h"
#include "Answer.h"
#include "User.h"
#include "Question.h"
#include <tuple>

class Service{
public:
	User user;
	Repo<Question>* questions;
	Repo<Answer>* answers;

	Service() = default;

	Service(const User& user, Repo<Question>* questions, Repo<Answer>* answers)
		: user(user), questions(questions), answers(answers)
	{}

	std::vector<Answer> AnswersToQuestion(const Question& q);
	int NumberOfAnswers(const Question& q);
	void SortQuestions();
	int FindBestMatchingQuestion(std::string matchStr);
	std::tuple<Answer, Answer, Answer> FindTop3Answers(const Question& q);
	void AddQuestion(std::string text);
	void AddAnswer(const Question& q, std::string text);
	bool AnswerByUser(const Answer& a) const;
};


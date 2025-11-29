#pragma once
#include "ParticipantServices.h"
#include "Domain.h"
#include "Repository.h"
#include "Utils.h"

class PresenterServices {
public:
	Repository<Question> questions, questionsCopy;
	Repository<Participant> participants;

	PresenterServices(const Repository<Question>& questions, const Repository<Question>& questionsCopy, const Repository<Participant>& participants)
		: questions(questions), questionsCopy(questionsCopy), participants(participants){
		SortQuestionsAscendingById(this->questions);
		SortQuestionsDescendingByScore(this->questionsCopy);
	}

	PresenterServices() = default;
	void AddQuestion(const Question& q);
};
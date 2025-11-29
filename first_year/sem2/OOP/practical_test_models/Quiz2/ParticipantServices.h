#pragma once
#include "Domain.h"
#include "Repository.h"

class ParticipantServices {
public:
	Participant* p;
	Repository<Question>* questions;

	ParticipantServices();
	ParticipantServices(Participant* _p, Repository<Question>* _questions);
	void Guess(std::string answer, int questionId);
};
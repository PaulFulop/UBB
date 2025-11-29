#include "ParticipantServices.h"

ParticipantServices::ParticipantServices(): p(nullptr), questions(nullptr) {}
ParticipantServices::ParticipantServices(Participant* _p, Repository<Question>* _questions): p(_p), questions(_questions){}

void ParticipantServices::Guess(std::string answer, int questionId) {
	for (const auto& q : questions->data)
		if (q.id == questionId) {
			if (q.answer == answer)
				p->score += q.score;
			return;
		}
}
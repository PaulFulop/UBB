#include "Service.h"
#include <algorithm>

std::vector<Answer> Service::AnswersToQuestion(const Question& q) {
	std::vector<Answer> answersToQ;

	for (const auto& a : answers->data)
		if (a.qId == q.id)
			answersToQ.push_back(a);

	return answersToQ;
}

int Service::NumberOfAnswers(const Question& q) {
	int count = 0;
	for (const auto& a : answers->data)
		if (a.qId == q.id) ++count;

	return count;
}

void Service::SortQuestions() {
	std::sort(questions->data.begin(), questions->data.end(), [this](const Question& q1, const Question& q2) {return NumberOfAnswers(q1) > NumberOfAnswers(q2); });
}

int Service::FindBestMatchingQuestion(std::string matchStr) {
	int maxSimilarityScore = 0, pos = -1;

	for (int i = 0; i < questions->data.size(); ++i) {
		if (maxSimilarityScore < questions->data[i].SimilarityScore(matchStr)) {
			pos = i;
			maxSimilarityScore = questions->data[i].SimilarityScore(matchStr);
		}
	}

	return pos;
}

std::tuple<Answer, Answer, Answer> Service::FindTop3Answers(const Question& q) {
	Answer a1, a2, a3;
	auto answersToQ = AnswersToQuestion(q);

	for (const auto& a : answersToQ) {
		if (a1.votes < a.votes) {
			a3 = a2;
			a2 = a1;
			a1 = a;
		}
		else if (a2.votes < a.votes) {
			a3 = a2;
			a2 = a;
		}
		else if (a3.votes < a.votes) {
			a3 = a;
		}
	}

	auto t = std::make_tuple(a1, a2, a3);
	return t;
}

void Service::AddQuestion(std::string text) {
	if (text == "") throw std::exception("There is no text for the question!");
	int maxId = -1;

	for (const auto& q : questions->data)
		if (q.id > maxId)
			maxId = q.id;

	auto newQ = Question(maxId + 1, text, user.name);
	questions->Add(newQ);
}

void Service::AddAnswer(const Question& q, std::string text) {
	if (text == "") throw std::exception("There is no text for the answer!");
	int maxId = -1;

	for (const auto& a : answers->data)
		if (a.id > maxId)
			maxId = a.id;
	
	auto newA = Answer(maxId + 1, q.id, user.name, text, 0);
	answers->Add(newA);
}

bool Service::AnswerByUser(const Answer& a) const {
	return a.name == user.name;
}
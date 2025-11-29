#include "PresenterServices.h"

void PresenterServices::AddQuestion(const Question& q) {
	for (const auto& qs : questions.data)
		if (qs.id == q.id)
			throw std::exception("Question with this id already exists.");

	questions.Add(q);
	questionsCopy.Add(q);

	SortQuestionsAscendingById(questions);
	SortQuestionsDescendingByScore(questionsCopy);
	questions.SaveToFile();
}
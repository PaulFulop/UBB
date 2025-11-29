#include "Utils.h"

std::vector<std::string> Tokenize(std::string input, char sep) {
	std::stringstream ss(input);
	std::vector<std::string> result;
	std::string token;

	while (getline(ss, token, sep))
		result.push_back(token);

	return result;
}

void SortQuestionsDescendingByScore(Repository<Question>& questions) {
	std::sort(questions.data.begin(), questions.data.end(), [](const Question& q1, const Question& q2) {return q1.score > q2.score; });
}
void SortQuestionsAscendingById(Repository<Question>& questions) {
	std::sort(questions.data.begin(), questions.data.end(), [](const Question& q1, const Question& q2) {return q1.id < q2.id; });
}
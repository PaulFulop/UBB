#include "Question.h"

std::istream& operator >> (std::istream& is, Question& q) {
	std::string line;
	std::getline(is, line);

	auto tokens = Tokenize(line, ',');
	if (tokens.size() != 3) return is;

	q = Question(std::atoi(tokens[0].c_str()), tokens[1], tokens[2]);
	return is;
}

std::ostream& operator << (std::ostream& os, const Question& q) {
	os << q.id << ',' << q.text << ',' << q.name;
	return os;
}

std::string Question::ToString() const {
	return std::to_string(id) + ", " + text;
}

int Question::SimilarityScore(std::string attempt) const {
	int score = 0;
	
	for (int i = 0; i < text.size() && i < attempt.size(); ++i)
		if (text[i] == attempt[i]) ++score;

	return score;
}
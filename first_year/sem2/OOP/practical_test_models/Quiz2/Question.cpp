#include "Domain.h"
#include "Utils.h"

Question::Question() : id(-1), text(""), answer(""), score(0){}

Question::Question(int _id, std::string _text, std::string _answer, int _score): id(_id), text(_text), answer(_answer), score(_score)  {}

std::string Question::ToStringPresenter() const noexcept {
	return std::to_string(id) + " " + text + " " + answer + " " + std::to_string(score);
}

std::string Question::ToStringParticipant() const noexcept {
	return std::to_string(id) + " " + text + " " + std::to_string(score);
}

std::istream& operator >> (std::istream& is, Question& q) {
	std::string questionString;
	getline(is, questionString);
	std::vector<std::string> tokens = Tokenize(questionString, ',');

	if (tokens.size() != 4)
		return is;

	Question questionCopy = Question(std::atoi(tokens[0].c_str()), tokens[1], tokens[2], std::atoi(tokens[3].c_str()));
	q = questionCopy;
	return is;
}

std::ostream& operator << (std::ostream& os, const Question& q) {
	os << q.id << "," << q.text << "," << q.answer << "," << q.score;
	return os;
}
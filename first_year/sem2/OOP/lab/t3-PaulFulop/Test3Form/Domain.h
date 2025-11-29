#pragma once
#include <string>

class Document {
public:
	std::string name, keywords, content;
	double desc_length;

	Document();
	Document(std::string _name, std::string _keywords, std::string _content);
	std::string ToString();

	double ComputeSimilarity(std::string substring);
};
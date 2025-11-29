#include "Domain.h"

Document::Document(): name(""), keywords(""), content(""), desc_length(0){}
Document::Document(std::string _name, std::string _keywords, std::string _content) : name(_name), keywords(_keywords), content(_content), desc_length(keywords.size()) {}
std::string Document::ToString() {
	return name + " | " + keywords;
}

double Document::ComputeSimilarity(std::string substring) {

	if (keywords.find(substring) == std::string::npos)
		return 0;

	return static_cast<double>(substring.size()) / desc_length;
}
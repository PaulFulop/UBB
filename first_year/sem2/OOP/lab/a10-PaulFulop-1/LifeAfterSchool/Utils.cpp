#include "Utils.h"
#include <sstream>

std::vector <std::string> Tokenize(std::string input, char sep)
{
	std::stringstream is{ input };
	std::vector<std::string> result;
	std::string token;

	while (getline(is, token, sep))
		result.push_back(token);

	return result;
}
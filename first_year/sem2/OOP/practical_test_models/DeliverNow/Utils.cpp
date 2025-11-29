#include "Utils.h"

std::vector<std::string> Tokenize(std::string input, char sep) {
	std::vector<std::string> tokens;

	std::stringstream ss(input);
	std::string token;
	while (std::getline(ss, token, sep))
		tokens.push_back(token);

	return tokens;
}
#include "Utils.h"

std::vector<std::string> Tokenize(std::string input, char sep) {
	std::stringstream ss(input);
	std::vector<std::string> tokens;
	std::string token;

	while (std::getline(ss, token, sep))
		tokens.push_back(token);

	return tokens;
}
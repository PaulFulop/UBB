#pragma once
#include <sstream>
#include <string>
#include <vector>

inline std::vector<std::string> Tokenize(std::string text, char sep) {
	std::stringstream ss(text);
	std::vector<std::string> tokens;
	std::string token;

	while (std::getline(ss, token, sep))
		tokens.push_back(token);

	return tokens;
}
#pragma once
#include <string>
#include <vector>
#include <sstream>

inline std::vector<std::string> Tokenize(std::string text, char sep) {
	std::vector<std::string> tokens;
	std::string token;
	std::stringstream ss(text);

	while (std::getline(ss, token, sep)) {
		tokens.push_back(token);
	}

	return tokens;
}
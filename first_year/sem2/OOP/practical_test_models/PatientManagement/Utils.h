#pragma once
#include<sstream>
#include<vector>
#include<string>

inline std::vector<std::string> Tokenize(std::string text, char sep) {
	std::stringstream ss(text);
	std::string token;
	std::vector<std::string> tokens;

	while (std::getline(ss, token, sep))
		tokens.push_back(token);

	return tokens;
}
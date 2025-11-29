#pragma once
#include <sstream>
#include <vector>
#include "Domain.h"
#include "Repository.h"
#include <algorithm>

std::vector<std::string> Tokenize(std::string input, char sep);
void SortQuestionsDescendingByScore(Repository<Question>& questions);
void SortQuestionsAscendingById(Repository<Question>& questions);
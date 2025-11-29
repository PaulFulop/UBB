#include "Agent.h"
#include "Utils.h"

std::string Agent::ToString() const {
	return name;
}

std::string Agent::ServiceAreaDetails() const {
	return std::to_string(areaX) + ',' + std::to_string(areaY) + ',' + std::to_string(areaRadius);
}

std::istream& operator >> (std::istream& is, Agent& agent) {
	std::string line;
	std::getline(is, line);

	std::vector<std::string> tokens = Tokenize(line, ';');
	if (tokens.size() != 5) return is;

	agent = Agent(tokens[0], Tokenize(tokens[1],','), std::atof(tokens[2].c_str()), std::atof(tokens[3].c_str()), std::atof(tokens[4].c_str()));
	return is;
}

std::ostream& operator << (std::ostream& os, const Agent& agent) {
	os << agent.name + ";";
	int i;
	for (i = 0; i < agent.streets.size() - 1; ++i) {
		os << agent.streets[i] + ";";
	}

	os << agent.streets[i] + ";" + std::to_string(agent.areaX) + ";" + std::to_string(agent.areaY) + ";" + std::to_string(agent.areaRadius);
	return os;
}
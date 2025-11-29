#pragma once
#include <string>
#include <vector>

class Agent {
public:
	std::string name;
	std::vector<std::string> streets;
	double areaX, areaY, areaRadius;

	Agent(std::string _name, std::vector<std::string> _streets, double _areaX, double _areaY, double _areaRadius): 
		name (_name), streets (_streets), areaX (_areaX), areaY (_areaY), areaRadius(_areaRadius) {}

	std::string ToString() const;
	std::string ServiceAreaDetails() const;
	friend std::istream& operator >> (std::istream& is, Agent& agent);
	friend std::ostream& operator << (std::ostream& os, const Agent& agent);

	Agent() = default;
};
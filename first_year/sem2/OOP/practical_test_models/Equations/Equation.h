#pragma once
#include <string>

class Equation {
public:
	double coef1, coef2, coef3;
	int grade;

	Equation();
	Equation(double _coef1, double _coef2, double _coef3);
	std::string ToString() const;
	bool IsImg() const;
};
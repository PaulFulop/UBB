#include "Equation.h"

Equation::Equation(): coef1(0), coef2(0), coef3(0), grade(0){}
Equation::Equation(double _coef1, double _coef2, double _coef3) : coef1(_coef1), coef2(_coef2), coef3(_coef3) {
	grade = coef1 ? 2 : !coef1 && coef2 ? 1 : !coef1 && !coef2 && coef3 ? 0 : 0;
}

std::string Equation::ToString() const {
	return (coef1 ? std::to_string(coef1) + "*x^2 " : "") + (coef2 ? (coef2 < 0 ? "" : "+") + std::to_string(coef2) + "*x " : "") + (coef3 ? std::to_string(coef3) : "");
}

bool Equation::IsImg() const {
	return coef2 * coef2 - 4 * coef1 * coef3 < 0;
}
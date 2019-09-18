//
// Created by savas on 20.02.2018.
//

#include "term.h"
#include <string>
double coefficient;
std::string variables;

bool term::operator<(const term & p) const
{
	return this->variables <  p.variables;
	//return this->coef <  p.coef;
}

term term::operator=(const term & t) const
{
	term term;
	term.variables = t.variables;
	term.coefficient = t.coefficient;
	return term;
}

bool term::operator==(const term & other) const
{
	return this->variables == other.variables && this->coefficient == other.coefficient;
	//return this->variables == other.variables;
}

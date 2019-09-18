//
// Created by savas on 18.02.2018.
//

#include "transition.h"


bool transition::operator<(const transition& p) const
{
	const auto x = this->state + this->next_state ;
	const auto y = p.state + p.next_state;
	return x < y;
}

transition transition::operator=(const transition& t) const // NOLINT
{
	transition transition;
	transition.input = t.input;
	transition.next_state = t.next_state;
	transition.state = t.state;
	transition.output = t.output;
	return transition;
}

bool transition::operator==(const transition& other) const
{
	return this->state == other.state && this->input == other.input &&
		this->next_state == other.next_state && this->output == other.output;
}

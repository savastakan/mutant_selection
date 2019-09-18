//
// Created by savas on 18.02.2018.
//

#ifndef TERM_H
#define TERM_H

#include <iostream>

using namespace std;

class term {
public:
    double coefficient{};
    string variables;

	bool operator<(const term & p) const;
	term operator=(const term & t) const;
	bool operator==(const term & other) const;
};


#endif //FFT_COEFFİCİENT_H

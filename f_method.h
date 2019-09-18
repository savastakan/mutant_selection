//
// Created by savas on 21.02.2018.
//

#ifndef FMETHOD_H
#define FMETHOD_H

#include<list>
#include<map>
#include<set>
#include <cmath>
#include "term.h"
#include"transition.h"

using namespace std;



struct coefficient_comparator final
{
	bool operator()(const term & player1, const term & player2) const
	{
		if(abs(player1.coefficient) == abs(player2.coefficient))
			return player1 < player2;
		return abs(player1.coefficient) < abs(player2.coefficient);
 
	}
};

class f_method final
{

public:
	//static double get_threshold(const list<term>& terms) ;
	//static list<term> remove_unnecessary_coefficients(double, const list<term>& terms, int);
	static set<transition> run(const pair<string, list<transition>>& transitions, int coefficient_size, int transition_size);
};


#endif //FMETHOD_H

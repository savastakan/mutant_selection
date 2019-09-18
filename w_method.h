//
// Created by savas on 28.11.2018.
//

#ifndef CODE_V2_W_METHOD_H
#define CODE_V2_W_METHOD_H

#include <list>
#include "transition.h"
using namespace std;

class w_method final
{

public:
	static set<list<string>> run(const map<string, map<string, pair<string, string>>>& formatted_transitions, const set<string>
	                      & inputs, const set<string>& states);
};


#endif //CODE_V2_W_METHOD_H

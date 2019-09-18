#ifndef STATE_H
#define STATE_H

#include<iostream>
#include<string>
#include<set>

#include"node.h"

using namespace std;

class state final
{
public:
	string input = "";
	set<node> nodes;
	void to_string();
};

#endif


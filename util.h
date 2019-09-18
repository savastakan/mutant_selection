//
// Created by savas on 18.02.2018.
//


#ifndef FFT_UTIL_H
#define FFT_UTIL_H

#include <regex>
#include<list>
#include<set>
#include <map>
#include "transition.h"



using namespace std;

class util
{
public:
	static pair<string,string> create_pair(const string& st1, const string& st2);
    static void create_fsm(const string& name, const int node, const int input, const int output, const int edge);
    static pair<string, list<transition>> read(const char* in_file_name);
	static set<string> get_inputs(const list<transition>& transitions);
	static pair<string, list<transition>> get_transitions_binary_form(const pair<string, list<transition>>& transitions);
	static set<string> get_states(const list<transition>& transitions);
	static map<string,map<string,pair<string,string>>> get_formatted_transitions(list<transition> transitions);

};

#endif //FFT_UTIL_H

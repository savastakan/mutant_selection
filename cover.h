#pragma once
#include <list>
#include <map>
#include <set>
using namespace std;

class cover
{
public:
	static set<list<string>> get_t(set<list<string>> p, set<list<string>> z);
	static set<list<string>> get_transition_cover_set(map<string, map<string, pair<string, string>>> transitions, const string& root);
	static list<string> get_path(map<string, map<string, pair<string, string>>>& transitions,
	                                         const string& root,
	                                         const string& dest);
};




#ifndef MUT_PROJECT_MUTATION_H
#define MUT_PROJECT_MUTATION_H

#include <map>
#include <list>
#include <set>
#include "transition.h"

using namespace std;

class mutation {
public:
    static pair<int, int> run(const string& start_state, const set<list<string>> &test_suite,
                              const map<string, map<string, pair<string, string>>> &original, const list<transition> &transitions);
};


#endif //MUT_PROJECT_MUTATION_H

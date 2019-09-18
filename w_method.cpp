//
// Created by savas on 28.11.2018.
//
#include <vector>
#include <set>
#include <map>
#include <stack>
#include "util.h"
#include "w_method.h"
#include "cover.h"


pair<string,pair<string,string>> get_state(pair<string,string> p, set<string> inputs, map<string,map<string,pair<string,string>>> transitions){
    pair<string,pair<string,string>> state;
    for(const auto &input : inputs){
            auto next_sate1 = transitions[p.first][input].first;
            auto next_sate2 = transitions[p.second][input].first;
            if ( next_sate1 != next_sate2){
                auto np = util::create_pair(next_sate1,next_sate2);
                state = make_pair(input,np);
                return state;
            }
    }
    return state;
}

list<string> get_outputs(pair<string,string> p, set<string> inputs, map<string,map<string,pair<string,string>>> transitions){
    list<string> tmp;
    for (const auto &input : inputs){
        auto output1 = transitions[p.first][input].second;
        auto output2 = transitions[p.second][input].second;
        if (output1 != output2){
            tmp.push_back(input);
            return tmp;
        }
    }
    return tmp;
}


set<list<string>> get_w(const set<string> &inputs, const set<string> &states, const map<string,map<string,pair<string,string>>> &transitions){
    vector<string> vector_states(states.begin(), states.end());
	map<pair<string, string>, list<string>> results;
	set<list<string>> w;
    map<pair<string,string>,pair<string,pair<string,string>>> remains;
    for (auto i = 0; i < static_cast<int>(vector_states.size()) - 1; ++i) {
        for (auto j = i+1; j < static_cast<int>(vector_states.size()); ++j) {
	        auto p = util::create_pair(vector_states[i],vector_states[j]);
            auto tmp = get_outputs(p, inputs, transitions);
            if (tmp.empty()) {
				remains[p] = get_state(p,inputs,transitions);
            } else {
				results[p] = tmp;
				w.emplace(tmp);
            }  
        }
    }
	
	for (const auto& r : remains) {
		stack<pair<string, string>> stack1;
		set<pair<string, string>> pairs;
		auto p = r.first;
		auto loop_check = true;
		while(results.count(p) == 0 && loop_check) {
			if (pairs.find(p) == pairs.end())
			{
				stack1.push(p);
				pairs.emplace(p);
				p = remains[p].second;
			}
			else loop_check = false;
			
		}
		if (!loop_check)
		{
			auto inputs1 = results[p];
			while (!stack1.empty()) {
				const auto pair1 = stack1.top();
				stack1.pop();
				inputs1.push_front(remains[pair1].first);
				results[pair1] = inputs1;
				w.emplace(inputs1);
				//remains.erase(pair1);
			}
		}
	
	}
    return w;
}





set<list<string>> w_method::run(const map<string, map<string, pair<string, string>>>& formatted_transitions, const set<string>
                                & inputs, const set<string>& states) {

	const auto z = get_w(inputs,states,formatted_transitions);
	return z;
}
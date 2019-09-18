#include "cover.h"
#include <queue>
#include <set>

set<list<string>> cover::get_t(set<list<string>> p, set<list<string>> z)
{
	set<list<string>> t;
	for (const auto& p1 : p)
	{

		for (const auto& z1 : z)
		{
			list<string> a;
			a.insert(a.end(), p1.begin(), p1.end());
			a.insert(a.end(), z1.begin(), z1.end());
			t.emplace(a);
		}


	}
	return t;

}

set<list<string>> cover::get_transition_cover_set(map<string, map<string, pair<string, string>>> transitions, const string& root) {
	queue<pair<string,list<string>>> q;
	set<list<string>> results;
	list<string> t;
	const auto r = make_pair(root, t);
	set<string> states;
	q.push(r);
	states.emplace(root);
	while (!q.empty()) {
		const auto node = q.front();
		q.pop();
		for (const auto& p : transitions[node.first])
		{
			auto input = p.first;
			auto next_state = p.second.first;
			auto inputs = node.second;
			inputs.push_back(input);
			results.insert(inputs);
			if (states.count(next_state) == 0)
			{
				q.push(make_pair(next_state, inputs));
				states.emplace(next_state);
				
			} 
		}
	}
	return results;
}

list<string> cover::get_path(map<string, map<string, pair<string, string>>>& transitions,
                                         const string& root,
                                         const string& dest) {
	queue<pair<string, list<string>>> q;
	list<string> t;
	const auto r = make_pair(root, t);
	set<string> states;
	q.push(r);
	states.emplace(root);
	while (!q.empty()) {
		const auto node = q.front();
		q.pop();
		for (const auto& p : transitions[node.first])
		{
			auto input = p.first;
			auto next_state = p.second.first;
			auto inputs = node.second;
			inputs.push_back(input);
			if(next_state == dest)
			{
				return inputs;
			}
			if (states.count(next_state) == 0)
			{
				q.push(make_pair(next_state, inputs));
				states.emplace(next_state);

			}
		}
	}
	return {};
}


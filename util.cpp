#include <fstream>
#include <sstream>
#include <iostream>
#include "util.h"

pair<string,string> util::create_pair(const string& st1, const string& st2){
	pair<string,string> p;
	if(st1<st2){
		p.first = st1;
		p.second = st2;
	} else {
		p.first = st2;
		p.second = st1;
	}
	return p;
}

string dec_to_binary(const int n,const int j)
{
	string result;
	for (auto i = j - 1; i >= 0; i--) {
		const auto k = n >> i;
		if (k & 1)
			result.append("1");
		else
			result.append("0");
	}
	return result;
}

int get_index(int n)
{
	auto index = 0;
	while (n > 0) {
		index++;
		n = n >> 1;
	}
	return index;
}


set<string> util::get_states(const list<transition>& transitions){
	set<string> states;
	for(auto t : transitions){
		states.emplace(t.state);
		states.emplace(t.next_state);
	}
	return states;
}

set<string> util::get_inputs(const list<transition>& transitions){
	set<string> inputs;
	for(auto transition : transitions) {

	    inputs.emplace(transition.input);
	}

	return inputs;
}

pair<string, list<transition>> util::get_transitions_binary_form(const pair<string, list<transition>>& transitions)
{
	map<string, int> states;
	auto index = 0;
	for( const auto& trans : transitions.second)
	{
		if (states.count(trans.state) == 0) states[trans.state] = index++;
		if (states.count(trans.next_state) == 0) states[trans.next_state] = index++;
	}
	const auto j = get_index(index);

	pair<string, list<transition>> result;
	result.first = dec_to_binary(states[transitions.first], j);
	for (const auto& trans: transitions.second)
	{
		transition t;
		t.state = dec_to_binary(states[trans.state], j);
		t.next_state = dec_to_binary(states[trans.next_state], j);
		t.input = trans.input;
		t.output = trans.output;
		result.second.push_back(t);
	}
	return result;
}

map<string,map<string,pair<string,string>>> util::get_formatted_transitions(list<transition> transitions){
    map<string,map<string,pair<string,string>>> formatted_transitions;
    for (auto transition : transitions){
        formatted_transitions[transition.state][transition.input] = make_pair(transition.next_state,transition.output);
    }
    return formatted_transitions;
}

pair<string, list<transition>> util::read(const char* in_file_name)
{
    pair<string,list<transition>> transitions;

    ifstream in_file;
    in_file.open(in_file_name);

    if (in_file.is_open())
    {
        string line;
        while (in_file)
        {
            getline(in_file, line);
			if(line.find(".r") == 0)
			{
				line = line.substr(2);
				line.erase(remove(line.begin(), line.end(), ' '), line.end());
				transitions.first = line;
			}
            else if (line.find('.') != 0 && ! line.empty()){
                const string pattern = R"(^(\w*)\s*(\w*)\s*(\w*)\s*(\w*))";
                const regex rgx(pattern);
                smatch match;
                if (regex_search(line, match, rgx))
                {
                    transition transition;
                    transition.input = match[1];
                    transition.state = match[2];
                    transition.next_state = match[3];
                    transition.output = match[4];
                    transitions.second.push_back(transition);
                    line = match.suffix().str();
                }
            }
        }
        in_file.close();
    }
    else
    {
        cout << "Cannot open file: " << in_file_name << endl;
    }
    return transitions;
}

void util::create_fsm(const string& name, const int node, const int input, const int output, const int edge) {
    stringstream st;
    st << "Genstate.exe -i " << input << " -o " << output << " -t " << edge << " -s "  << node <<" " << name;
    cout << st.str().c_str();
    system(st.str().c_str());
}





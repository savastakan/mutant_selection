#include "f_method.h"
#include "util.h"
#include "cover.h"

struct term_comparator
{
	bool operator()(const term & term1, const term & term2) const
	{
		if(abs(term1.coefficient) == abs(term2.coefficient))
			return term1 < term2;
		return abs(term1.coefficient) < abs(term2.coefficient);
 
	}
};

set<list<string>> get_test_cases(map<int, list<transition>> solution, map<string, map<string, pair<string, string>>>& transitions,
	const string& root) {
	set<list<string>> result;
	for (const auto& pair : solution) {
		auto t = solution[pair.first].front();
		solution[pair.first].pop_front();
		auto input = cover::get_path(transitions, root, t.state);
		input.push_back(t.input);
		for (const auto& pair2 : solution[pair.first]) {
			input.push_back(pair2.input);
		}
		result.insert(input);
	}
	return result;
}



bool check_transition_with_coefficient(string pattern, string a,string b) {
	auto size = 0;
	for (unsigned int i = 0; i < a.length(); i++) {
		if (pattern[i] == '1') {
			if (a[i] != b[i]) {
				size++;
			} else
			{
				return false;
			}
		} else
		{
			if (a[i] != b[i]) return false;
		}
	}
	return size % 2 == 1;
}

map<int, list<string>> get_inputs_form_next_states(list<transition> transitions) {
	map<int, list<string>> next_states;
	for (auto transition : transitions) {
		for (unsigned int i = 0; i < transition.next_state.length(); i++) {
			if (transition.next_state[i] == '1') {
				next_states[i].push_back(transition.state + transition.input);
			}
		}
	}
	return next_states;
}

map<int, list<string>> get_inputs_form_outputs(list<transition> transitions) {
	map<int, list<string>> outputs;
	for (auto transition : transitions) {
		for (unsigned int i = 0; i < transition.output.length(); i++) {
			if (transition.output[i] == '1') {
				outputs[i].push_back(transition.state + transition.input);
			}
		}
	}
	return outputs;
}

string variables(const int input, const int size)
{
	string ins;
	for (auto i = 0; i < size; i++) {
		const auto tmp = (input >> i) & 0x1; // NOLINT
		ins.append(to_string(tmp));
	}
	return ins;
}

int bool_func(const int input, list<string>  inputs, const int size)
{
	string ins;
	for (auto i = 0; i < size; i++) ins.append(to_string((input >> i) & 0x1)); // NOLINT
	if (find(inputs.begin(), inputs.end(), ins) != inputs.end()) return 1;
	else return 0;
}


list<term> calculate_fourier(const int input, const list<string>& inputs)
{
	list<term> terms;
	for (auto i = 0; i< pow(2, input); i++) {
		double a = 0;
		for (auto j = 0; j< pow(2, input); j++) {
			auto nx = 1.0;
			for (auto m = 0; m<input; m++) {
				if (((i >> m) & 0x1) == 1 && ((j >> m) & 0x1) == 1) { // NOLINT
					nx *= (-1.0);
				}
			}
			auto fn = bool_func(j, inputs, input);

			if (fn >= 1)fn = -1; else if (fn == 0) fn = 1;
			a += (nx*fn);
		}
		term term;
		term.variables = variables(i, input);
		term.coefficient = a / pow(2, input);
		terms.push_back(term);

	}
	return terms;
}

list<term> get_terms(map<int, list<string>> inputs, const int size)
{
	list<term> terms;
	for (const auto& pair : inputs) {
		const auto t = calculate_fourier(size, pair.second);
		terms.insert(terms.end(), t.begin(), t.end());
	}
	return terms;
}

 map<int, list<transition>> create_solution( set<transition> transitions) {
	map<int, list<transition>> solution;

	for (auto &transition : transitions) {
		const auto size = static_cast<int>(solution.size());
		if (size == 0) {
			solution[0].push_back(transition);
		}
		else {
			auto check = true;
			for (auto &key : solution) {
				const auto tmp_last = solution[key.first].back().next_state;
				const auto tmp_last2 = transition.state;
				const auto tmp_first = solution[key.first].front().state ;
				const auto tmp_first2 = transition.next_state;

				if (tmp_last==tmp_last2) {
					solution[key.first].push_back(transition);
					check = false;
					break;
				}
				else if (tmp_first == tmp_first2) {
					solution[key.first].push_front(transition);
					check = false;
					break;
				}
			}
			if (check) {
				solution[size].push_back(transition);
			}
		}
	}
	return solution;
}
    set<transition> find_transition(list<term> terms, const list<transition>& transitions, const int coefficient_size, const int transition_size) {
		terms.sort(term_comparator());
        set<transition> trans_set;
        set<term> terms_set;
        for (auto i =0; i < static_cast<int>(terms.size()); i++)
        {
	        const auto term = terms.front();
			terms.pop_front();
            //if (term.coefficient == 0){
                for(const auto& trans : transitions) {
                    if (check_transition_with_coefficient(term.variables, trans.state, trans.next_state)) {
                        trans_set.emplace(trans);
                        if(static_cast<int>(trans_set.size()) == transition_size){
                            return trans_set;
                        }
                        terms_set.insert(term);
                    }
                }

           //}
            if (static_cast<int>(terms_set.size()) == coefficient_size){
                return trans_set;
            }
        }
        return trans_set;
    }



set<transition> f_method::run(const pair<string, list<transition>>& transitions, const int coefficient_size, const int transition_size)
{
	//auto transitions_binary_form = util::get_transitions_binary_form(transitions);

	const auto size = transitions.second.front().state.length() + transitions.second.front().input.length();

	const auto outputs = get_inputs_form_outputs(transitions.second);
	//const auto next_states = get_inputs_form_next_states(transitions);

	const auto terms = get_terms(outputs, static_cast<int>(size));
	//const auto temp = get_terms(next_states, static_cast<int>(size));
	//terms.insert(terms.end(), temp.begin(), temp.end());

	const auto reduced_transitions = find_transition(terms, transitions.second,coefficient_size,transition_size);

	//const auto solution = create_solution(reduced_transitions);
	//auto formatted_transitions = util::get_formatted_transitions(transitions.second);
	//auto inputs = get_test_cases(solution, formatted_transitions,transitions.first);
	return reduced_transitions;
}

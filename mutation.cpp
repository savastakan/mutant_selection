//
// Created by savas on 24.05.2019.
//

#include "mutation.h"

list<string> get_output( const string& start_state, const list<string>& test_case, const map<string,map<string,pair<string,string>>>& transitions){
    list<string> output;
    auto state = start_state;
    for (const auto& input : test_case){
        if (transitions.count(state) > 0){
            if (transitions.at(state).count(input) > 0){
				auto out = transitions.at(state).at(input).second;
                state = transitions.at(state).at(input).first;
                output.push_front(out);
            } else {
                return output;
            }
        } else return output;
    }
    return output;
}

string change(const string& output){
    string new_output;
    for (auto o : output)
    {
        if (o =='0') {
            new_output.append("1");
        } else new_output.append("0");
    }
    return new_output;
}

bool test(const string& original_start_state,const string& mutant_start_state, const list<string>& test_case,const map<string,map<string,pair<string,string>>>& original, const map<string,map<string,pair<string,string>>>& mutant ) {
    const auto output1 = get_output(original_start_state, test_case, original);
    const auto output2 = get_output(mutant_start_state, test_case, mutant);
    return output1 == output2;
}

pair<int,int> process(const string& start_state, const set<list<string>>& test_suite, const transition& t, const map<string,map<string,pair<string,string>>>& original){
    auto state = t.state;
    auto input = t.input;
    auto next_state = t.next_state;
    auto output = t.output;

    map<string,map<string,pair<string,string>>> mutant;
    int number_of_mutants = 0;
    int number_of_killed_mutant = 0;


    mutant = original; // Reverse of Transition(ROT)
    mutant.at(state).erase(input);
    if (!mutant[next_state].count(input)){
        mutant[next_state][input] = make_pair(state,output);
    }
    number_of_mutants++;
    for (const auto& test_case : test_suite){
        if(!test(start_state,start_state,test_case,original,mutant)){
            number_of_killed_mutant++;
        }
    }


    mutant = original;  // Missing of Transition(MOT)
    mutant.at(state).erase(input);

    number_of_mutants++;
    for (const auto& test_case : test_suite){

        if(!test(start_state,start_state,test_case,original,mutant)){
            number_of_killed_mutant++;
        }
    }


    mutant = original; //Change of Input (COI)
    mutant.at(state).erase(input);
    mutant[state][change(input)] = make_pair(next_state,output);

    number_of_mutants++;
    for (const auto& test_case : test_suite){

        if(!test(start_state,start_state,test_case,original,mutant)){
            number_of_killed_mutant++;
        }
    }

	/*
    mutant = original; //Missing of Input (MOI)
    mutant.at(state).erase(input);
    mutant[state]["X"] = make_pair(next_state,output);

    number_of_mutants++;
    for (const auto& test_case : test_suite){

        if(!test(start_state,start_state,test_case,original,mutant)){
            number_of_killed_mutant++;
        }
    }
	*/

    mutant = original; //Change of Output (COO)
    mutant[state][input].second = change(output);

    number_of_mutants++;
    for (const auto& test_case : test_suite){

        if(!test(start_state,start_state,test_case,original,mutant)){
            number_of_killed_mutant++;
        }
    }

	/*
    mutant = original; //Missing of Output (MOO)
    mutant[state][input].second = "X";


    number_of_mutants++;
    for (const auto& test_case : test_suite){

        if(!test(start_state,start_state,test_case,original,mutant)){
            number_of_killed_mutant++;
        }
    }
	*/
	/*
    mutant = original; //Start State Changed (SSC)
    number_of_mutants++;
    for (const auto& test_case : test_suite){

        if(!test(start_state,next_state,test_case,original,mutant)){
            number_of_killed_mutant++;
        }
    }
	*/

    return make_pair(number_of_mutants, number_of_killed_mutant);
}

pair<int,int> compute(const  string& start_state, const set<list<string>>& test_suite, const map<string,map<string,pair<string, string>>>& original,const list<transition>& transitions){
    auto p = make_pair(0,0);
    map<string,map<string,pair<string,string>>> mutant;
    for (const auto& t : transitions) {
        auto temp = process(start_state,test_suite,t,original);
        p.first += temp.first;
        p.second += temp.second;
    }
    return p;
}



pair<int,int> mutation::run(const string& start_state, const set<list<string>>& test_suite, const map<string,map<string,pair<string,string>>>& original,const list<transition>& transitions)
{
 return compute(start_state,test_suite,original,transitions);
}

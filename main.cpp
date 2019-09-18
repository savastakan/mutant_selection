#include"util.h"
#include "w_method.h"
#include "f_method.h"
#include "cover.h"
#include "mutation.h"

void print(string name , set<list<string>> const &test_suite)
{
    cout << "****************************"<<name<<"********************************" << endl << "[";
    for (auto const& list : test_suite){
        cout << ",{";
        for (auto const& i: list) {
            cout << i << ",";
        }
        cout << "}";
    }
    cout << "]" << endl;
}

void print_value(int space ,vector<double> standard_mutation_results,vector<double> f_mutation_results)
{
    cout  << endl;
    cout <<"----------------------standard_mutation_results--------------------------"<<endl;
    for (unsigned int i = 0; i < static_cast<int>(standard_mutation_results.size()); i++) {
        cout << "(" << i+space << "," << standard_mutation_results.at(i) << ")" << endl;
    }
    cout << "************f_mutation_results**********" << endl;
    for (unsigned int i = 0; i < static_cast<int>(f_mutation_results.size()); i++) {
        cout << "(" << i+space << "," << f_mutation_results.at(i) << ")" << endl;
    }
}

void run(){
    auto state = 2;
    auto input = 1;
    auto output = 2;
    const int sample_size = 5;
    const auto variable_size = 20;
    const  auto space = output;
    //const char *file = "deneme.kiss2";

    vector<double> standard_mutation_results, f_mutation_results;

    for (auto k = 0; k < variable_size; k++)
    {

        pair<double,double>  standard_mutation, f_mutation;
        for (auto i = 0; i < sample_size; i++)
        {

            util::create_fsm("deneme.kiss2", state , input , output , (int) pow(2,input)*state);
            const auto transitions = util::read("deneme.kiss2");
            const auto transitions_binary_form = util::get_transitions_binary_form(transitions);
            const auto formatted_transitions = util::get_formatted_transitions(transitions_binary_form.second);
            const auto inputs = util::get_inputs(transitions_binary_form.second);
            const auto states = util::get_states(transitions_binary_form.second);

            /**************************************************/
            const auto z = w_method::run(formatted_transitions, inputs, states);
            const auto p = cover::get_transition_cover_set(formatted_transitions, transitions_binary_form.first);
            auto w = cover::get_t(p, z);
            /**************************************************/
            const auto temp1 = mutation::run(transitions_binary_form.first,w,formatted_transitions,transitions_binary_form.second);
            standard_mutation.first += temp1.first;
            standard_mutation.second += temp1.second;
            /**************************************************/
            const auto f_transitions = f_method::run(transitions_binary_form, 10, 10);
            list<transition> f_trans(begin(f_transitions), end(f_transitions));
            /**************************************************/
            const auto temp2 = mutation::run(transitions_binary_form.first,w,formatted_transitions,f_trans);
            f_mutation.first += temp2.first;
            f_mutation.second += temp2.second;

        }
        const double standard_mutation_mean = standard_mutation.second / standard_mutation.first;
        const double f_mutation_mean = f_mutation.second / f_mutation.first;
        standard_mutation_results.push_back(standard_mutation_mean);
        f_mutation_results.push_back(f_mutation_mean);
        output++;
    }
    print_value(space,standard_mutation_results,f_mutation_results);
}

void start(const char *file)
{
    const auto transitions = util::read(file);
    const auto transitions_binary_form = util::get_transitions_binary_form(transitions);
    const auto formatted_transitions = util::get_formatted_transitions(transitions_binary_form.second);
    const auto inputs = util::get_inputs(transitions_binary_form.second);
    const auto states = util::get_states(transitions_binary_form.second);

    /**************************************************/
    const auto z = w_method::run(formatted_transitions, inputs, states);
    const auto p = cover::get_transition_cover_set(formatted_transitions, transitions_binary_form.first);
    auto w = cover::get_t(p, z);

    print("W-method",w);

    const auto f_transitions = f_method::run(transitions_binary_form, 10, 10);

    list<transition> f_trans(begin(f_transitions), end(f_transitions));

    const auto  standard_mutation_results = mutation::run(transitions_binary_form.first,w,formatted_transitions,transitions_binary_form.second);
    const auto  f_mutation_results = mutation::run(transitions_binary_form.first,w,formatted_transitions,f_trans);

    cout << "standard_mutation_results - number_of_mutants: " << standard_mutation_results.first << endl;
    cout << "standard_mutation_results - number_of_killed_mutant: " << standard_mutation_results.second << endl;

    cout << "f_mutation_results - number_of_mutants: " << f_mutation_results.first << endl;
    cout << "f_mutation_results - number_of_killed_mutant: " << f_mutation_results.second << endl;
}
int main(int argc, char** argv)  {
    auto state = 6;
    auto input = 2;
    auto output = 2;
    util::create_fsm("deneme.kiss2", state , input , output , (int) pow(2,input)*state);
    //run();
    start("deneme.kiss2");
    //start(argv[1]);
    return 0;
}

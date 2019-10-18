/*
    To run this example:
    $ bash scripts/compile.sh mdp_example && ./build/examples/mdp_example 
*/

#include <iostream>
#include <vector>
#include <string>
#include "mdp.h"
#include "utils.h"

using namespace std;

int main(void)
{
    /*   Defining a simple MDP with 3 states and 2 actions  */    

    mdp::Chain mdp(20);


    cout << mdp.id << endl << endl; 

    int max_t = 15;

    // Setting up the history, with two extra variables stored.
    mdp.history.reserve_mem(max_t, 2);
    std::vector<std::string> names = {"extra_var_1", "extra_var_2"};
    mdp.history.set_names(names);

    for(int i = 0; i < max_t; i++)
    {
        int state = mdp.state;
        int action = mdp.action_space.sample();
        std::vector<double> extra_vars = {0.001, 0.002}; // values of extra variables

        // take step
        mdp::StepResult<int> step_result = mdp.step(action);

        // append to history
        mdp.history.append(state, action, step_result.reward, step_result.next_state, extra_vars);

        if (step_result.done) break;
    }

    // print history
    mdp.history.print(max_t);

    return 0;
}
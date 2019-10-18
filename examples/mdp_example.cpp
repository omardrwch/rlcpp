/*
    To run this example:
    $ bash scripts/compile.sh mdp_example && ./build/examples/mdp_example 
*/

#include <iostream>
#include "mdp.h"
#include "utils.h"

using namespace std;

int main(void)
{
    /*   Defining a simple MDP with 3 states and 2 actions  */    

    mdp::Chain mdp(20);


    cout << mdp.id << endl << endl; 

    int max_t = 15;
    mdp.history.reserve_mem(max_t);

    for(int i = 0; i < max_t; i++)
    {
        int state = mdp.state;
        int action = mdp.action_space.sample();

        // take step
        mdp::StepResult<int> step_result = mdp.step(action);

        // append to history
        mdp.history.append(state, action, step_result.reward, step_result.next_state);

        if (step_result.done) break;
    }

    // print history
    mdp.history.print(max_t);

    return 0;
}
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

    mdp::Chain mdp(3);


    cout << mdp.id << endl << endl; 

    for(int i = 0; i < 100; i++)
    {
        int state = mdp.state;
        int action = mdp.action_space.sample();

        mdp::StepResult<int> step_result = mdp.step(action);

        cout << "action = " << action << " | ";
        cout << "state = " << state << " | ";
        cout << "next state = " << step_result.next_state << " | ";
        cout << "done    = " << step_result.done << " | ";
        cout << "reward    = " << step_result.reward << endl;

        if (step_result.done)
        {
            break;
        }
    }

    return 0;
}
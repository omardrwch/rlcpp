/*
    To run this example:
    $ bash scripts/compile.sh mdp_example && ./build/examples/mdp_example 
*/

#include <iostream>
#include "mdp.h"
#include "finitemdp.h"
#include "utils.h"

using namespace std;

int main(void)
{
    /*   Defining a simple MDP with 3 states and 2 actions  */    
    int ns = 3;
    int na = 2;

    utils::vec_3d transisions; 
    utils::vec_3d rewards; 

    for(int s = 0; s < ns; s++)
    {
        transisions.push_back(std::vector<std::vector<double>>());
        rewards.push_back(std::vector<std::vector<double>>());
        for(int a = 0; a < na; a++)
        {
            transisions[s].push_back(std::vector<double>());
            rewards[s].push_back(std::vector<double>());
            for(int next_s = 0; next_s < ns; next_s++)
            {
                double prob = 0;
                double reward = 0;
                // First action
                if (a == 0)
                {
                    if(s == 0 && next_s == 1) prob = 1.0;
                    if(s == 1 && next_s == 2) prob = 1.0;
                    if(s == 2 && next_s == 2) {prob = 1.0; reward = 1.0;}
                 }
                // Second action
                if (a == 1)
                {
                    if(s == 0 && next_s == 0) prob = 1.0;
                    if(s == 1 && next_s == 0) prob = 1.0;
                    if(s == 2 && next_s == 2) {prob = 1.0; reward = 1.0;}
                 }
                transisions[s][a].push_back(prob);
                rewards[s][a].push_back(reward);
            }
            // utils::printvec(rewards[s][a]);
        }
    }       


    mdp::FiniteMDP mdp(rewards, transisions);
    for(int i = 0; i < 5; i++)
    {
        cout << "state = " << mdp.state << " | ";
        int action = mdp.action_space.sample();
        cout << "action = " << action << " | ";

        mdp::StepResult<int> step_result = mdp.step(action);

        cout << "next state = " << step_result.next_state << " | ";
        cout << "reward    = " << step_result.reward << endl;
    }

    return 0;
}
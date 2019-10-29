/*
    To run this example:
    $ bash scripts/compile.sh gridworld_example && ./build/examples/gridworld_example
*/

#include <iostream>
#include <vector>
#include <string>
#include "mdp.h"
#include "utils.h"
#include "mountaincar.h"

using namespace std;
using namespace utils::vec;


int main(void)
{
    /*   

        Defining a GridWorld
            
    */
   
    double fail_prob = 0.0;  // failure probability
    double sigma = 0.1;       // reward = exp( - dist(next_state, goal_state)^2 / sigma^2)
    mdp::GridWorld mdp(4, 4, fail_prob, sigma);
    cout << endl << mdp.id << endl;

    // render 
    mdp.render();

    /*   

        Take some steps
            
    */
   cout << "Right " << endl;
   mdp.step(1);
   mdp.render();

   cout << "Down " << endl;
   mdp.step(3);
   mdp.render();


    /*   

        Value iteration
            
    */   

    int horizon = 10;
    mdp::EpisodicVI vi(mdp, horizon);
    vi.run();

    
    std::cout << "Value function at h = 0: " << std::endl;
    mdp.render_values(vi.V[0]);



    // cout << "Value function" << endl;
    // for (int h=0; h<=horizon; h++)
    // {
    //   printvec(vi.V[h]);
    // }

    // cout << "Policy" << endl;
    // for (int h=0; h<horizon; h++)
    // {
    //   printvec(vi.greedy_policy[h]);
    // }


    return 0;
}

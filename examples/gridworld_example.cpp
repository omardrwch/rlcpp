/*
    To run this example:
    $ bash scripts/compile.sh gridworld_example && ./build/examples/gridworld_example
*/

#include <iostream>
#include <vector>
#include <string>
#include "rlcpp.h"

using namespace std;
using namespace utils::vec;


int main(void)
{
    /*   

        Defining a GridWorld
            
    */
   
    double fail_prob = 0.2;  // failure probability
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


    /* 

        Checking transition probabilities

    */
    int state = 0; 
    std::cout << "Transitions at state " << state << ", action left: " << std::endl;
    mdp.render_values(mdp.transitions[state][0]);
    std::cout << "Transitions at state " << state << ", action right: " << std::endl;
    mdp.render_values(mdp.transitions[state][1]);
    std::cout << "Transitions at state " << state << ", action up: " << std::endl;
    mdp.render_values(mdp.transitions[state][2]);
    std::cout << "Transitions at state " << state << ", action down: " << std::endl;
    mdp.render_values(mdp.transitions[state][3]);

    return 0;
}

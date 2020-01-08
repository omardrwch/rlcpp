/*
    To run this example:
    $ bash scripts/compile.sh gridworld_example && ./build/examples/gridworld_example
*/

#include <iostream>
#include <vector>
#include <string>
#include "episodicvi.h"
#include "gridworld.h"

using namespace std;
using namespace utils::vec;


int main(void)
{
    /*   

        Defining a GridWorld
            
    */
   
    double fail_prob = 0.0;  // failure probability
    double reward_smoothness = 0.0;      // reward = exp( - dist(next_state, goal_state)^2 / reward_smoothness^2)
    double sigma = 0.1;  // reward noise (Gaussian)
    mdp::GridWorld mdp(2, 2, fail_prob, reward_smoothness, sigma);

    cout << endl << mdp.id << endl;
    cout << endl << mdp.reward_function.noise_type << endl;


    // render 
    mdp.render();
    cout << endl;

    // set mdp seed
    mdp.set_seed(11);

    /*   

        Take some steps
            
    */

    mdp::StepResult<int> outcome; 
    cout << "Right " << endl;
    outcome = mdp.step(1);
    mdp.render();
    cout << "Reward = " << outcome.reward  << endl << endl; 
   
    cout << "Down " << endl;
    outcome = mdp.step(3);
    mdp.render();
    cout << "Reward = " << outcome.reward << endl << endl; 

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

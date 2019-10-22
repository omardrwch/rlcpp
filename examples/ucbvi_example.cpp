/*
    To run this example:
    $ bash scripts/compile.sh ucbvi_example && ./build/examples/ucbvi_example
*/

#include <iostream>
#include <vector>
#include <string>
#include "mdp.h"
#include "episodicvi.h"
#include "ucbvi.h"
#include "utils.h"

using namespace std;
using namespace utils::vec;

std::vector<double> run_simulation(mdp::FiniteMDP& mdp, int horizon, int nb_episodes, vec_2d& trueV)
{
    double old_regret = 0, episode_regret;
    int init_state;
    online::UCBVI algo(mdp, horizon);
    algo.reset();
    std::vector<double> regret;
    regret.reserve(nb_episodes+1);
    regret.push_back(old_regret);
    for (int k=0; k < nb_episodes; ++k)
    {
        if ((k + 1) % 100 == 0)
        {
            cout << "Episode = " << (k + 1) << endl;
            cout << "rewards in last episode = " << algo.all_episode_rewards[k] << endl;
        }
        init_state = algo.run_episode();
        episode_regret = trueV[0][init_state] - algo.episode_value[k];
        old_regret = old_regret + episode_regret;
        regret.push_back(old_regret);
    }
    return regret;
}

int main(void)
{
    /*   Defining a simple MDP with 3 states and 2 actions  */

    mdp::Chain mdp(4);
    cout << mdp.id << endl << endl;

    int horizon = 7;

    // compute true value function
    mdp::EpisodicVI vi(mdp, horizon);
    vi.run();
    vec_2d& trueV = vi.V;

    // run simulation
    std::vector<double> regret = run_simulation(mdp, horizon, 200, trueV);

    // Save history
    mdp.history.to_csv("data/ucbvi.csv");

    return 0;
}

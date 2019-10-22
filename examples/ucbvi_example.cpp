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

std::vector<double> run_simulation(mdp::FiniteMDP& mdp, int horizon, int nb_episodes, vec_2d& trueV,
                                   double scale_factor, std::string bound_type)
{
    double old_regret = 0, episode_regret;
    int init_state;
    online::UCBVI algo(mdp, horizon, scale_factor, bound_type);
    algo.reset();
    std::vector<double> regret;
    regret.reserve(nb_episodes+1);
    regret.push_back(old_regret);
    for (int k=0; k < nb_episodes; ++k)
    {
        if ((k + 1) % 50 == 0)
        {
            cout << "Episode = " << (k + 1) << endl;
            cout << "rewards in last episode = " << algo.all_episode_rewards[algo.all_episode_rewards.size()-1] << endl;
        }
        init_state = algo.run_episode(trueV);
        episode_regret = trueV[0][init_state] - algo.episode_value[k];
        old_regret = old_regret + episode_regret;
        regret.push_back(old_regret);
        // cout << endl << "Episode " << k << endl;
        // for (int s=0; s < mdp.ns; ++s)
        //   for (int a=0; a<mdp.na; ++a)
        //   {
        //     std::cout << s << ", " << a << " ";
        //     printvec(algo.Phat[s][a]);
        //     printvec(algo.Rhat[s][a]);
        //   }
        // cout << "Policy" << endl;
        // for (int h=0; h < horizon; ++h) {
        //   printvec(algo.policy[h]);
        // }
    }
    return regret;
}

int main(void)
{
    /*   Defining a simple MDP with 3 states and 2 actions  */

    mdp::Chain mdp(4);
    cout << mdp.id << endl << endl;

    int horizon = 4;
    double scale_factor = 1;
    std::string bound_type = "hoeffding";

    // compute true value function
    mdp::EpisodicVI vi(mdp, horizon);
    vi.run();
    vec_2d& trueV = vi.V;

    for (int h=0; h < horizon; ++h)
    {
        printvec(vi.greedy_policy[h]);
    }



    // run simulation
    std::vector<double> regret = run_simulation(mdp, horizon, 3000, trueV,
                                 scale_factor, bound_type);

    // Save history
    mdp.history.to_csv("data/ucbvi_" + bound_type + ".csv");

    return 0;
}

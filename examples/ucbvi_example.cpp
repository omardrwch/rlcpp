/*
To run this example:
$ bash scripts/compile.sh ucbvi_example && ./build/examples/ucbvi_example
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <future>
#include <sstream>
#include <algorithm>
#include "mdp.h"
#include "episodicvi.h"
#include "ucbvi.h"
#include "utils.h"

using namespace std;
using namespace utils::vec;

class WorkerThread
{
public:
    WorkerThread(std::string name): name(name) {}

    void operator()(int nb_episodes,
                    int horizon, double scale_factor, std::string bound_type,
                    const vec_2d& trueV)
    {
        mdp::Chain mdp(4, 0.01);
        // define learning algorithm
        online::UCBVI algo(mdp, horizon, scale_factor, bound_type, true);

        double old_regret = 0, episode_regret;
        int init_state;
        int verbose = 0;

        // initialize regret
        regret.reserve(nb_episodes+1);
        regret.push_back(old_regret);

        algo.reset();
        for (int k=0; k < nb_episodes; ++k)
        {
            if ((verbose > 0) && ((k + 1) % 50 == 0))
            {
                cout << "Episode = " << (k + 1) << endl;
                cout << "rewards in last episode = " << algo.all_episode_rewards[algo.all_episode_rewards.size()-1] << endl;
            }
            init_state = algo.run_episode(trueV);

            episode_regret = trueV[0][init_state] - algo.episode_value[k];
            old_regret = old_regret + episode_regret;
            regret.push_back(old_regret);
        }
        // Save history
        mdp.history.to_csv("data/" + name + ".csv");

        // for (int s=0; s<mdp.ns; s++)
        // for (int a=0; a<mdp.na;++a){
        //   utils::vec::printvec(algo.Phat[s][a]);
        // }
    }

    std::vector<double> regret;
    std::string name;
};


void run_par_simulations(int nb_simulations,
                         int nb_episodes,
                         int horizon, double scale_factor, std::string bound_type,
                         vec_2d& trueV)
{
    unsigned int c = std::thread::hardware_concurrency();
    std::cout << "Number of cores: " << c << endl;
    std::vector<std::thread> threadList;
    std::vector<WorkerThread> workerList;
    for(int i = 0; i < nb_simulations; i++)
    {
        std::ostringstream ss;
        ss << "ucbvi_chain_" << bound_type << "_" << i;
        workerList.push_back(WorkerThread(ss.str()));
    }
    for(int i = 0; i < workerList.size(); i++)
    {
        threadList.push_back(
            std::thread(
                std::ref(workerList[i]),
                nb_episodes,
                horizon, scale_factor, bound_type,
                std::ref(trueV)
            )
        );
    }

    // std::for_each(threadList.begin(),threadList.end(), std::mem_fn(&std::thread::join));
    for(int i = 0; i < nb_simulations; i++)
    {
        if (threadList[i].joinable())
            threadList[i].join();
    }

    std::cout << "All threads have finished" << std::endl;

    std::string output_file = "data/ucbvi_chain_" + bound_type + ".csv";
    std::ofstream myfp(output_file);

    if (myfp.is_open())
    {
        for (int k=0; k<nb_episodes; ++k )
        {
            for(int i = 0; i < nb_simulations; i++)
            {
                myfp << workerList[i].regret[k];
                if (i < nb_simulations - 1)
                    myfp << ",";
            }
            myfp << endl;
        }
        myfp.close();
    }
}


int main(void)
{
    /*   Defining a simple MDP with 3 states and 2 actions  */
    std::srand(4);

    int horizon = 10;
    double scale_factor = 1;
    std::string bound_type = "bernstein";

    mdp::Chain mdp(4);
    cout << mdp.id << endl << endl;

    // compute true value function
    mdp::EpisodicVI vi(mdp, horizon);
    vi.run();
    vec_2d& trueV = vi.V;

    for (int h=0; h < horizon; ++h)
    {
        printvec(vi.greedy_policy[h]);
    }


    run_par_simulations(10, 10000, horizon, scale_factor, bound_type, trueV);


    return 0;
}

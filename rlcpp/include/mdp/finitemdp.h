#ifndef __FINITEMDP_H__
#define __FINITEMDP_H__

/**
 * @file
 * @brief Base class for finite MDPs.
 */

#include <vector>
#include "mdp.h"
#include "utils.h"

namespace mdp
{
    class FiniteMDP: public MDP<int, int>
    {
    public:
        /**
         * @param _mean_rewards
         * @param _transitions
         * @param _seed random seed
         */
        FiniteMDP(utils::vec_3d _mean_rewards, utils::vec_3d _transitions, unsigned _seed = 42);
        ~FiniteMDP(){};

        /**
         * 3d vector such that mean_rewards[s][a][s'] is the mean reward obtained when the 
         * state s' is reached by taking action a in state s.
         */
        utils::vec_3d mean_rewards;

        /**
         * 3d vector such that transitions[s][a][s'] is the probability of reaching
         * state s' by taking action a in state s.
         */
        utils::vec_3d transitions;

        /**
         * For random number generation
         */
        utils::Random randgen;

        // Members of base class
        int state;
        std::string id; 
        int reset();
        StepResult<int> step(int action);
    };  

    FiniteMDP::FiniteMDP(utils::vec_3d _mean_rewards, utils::vec_3d _transitions, unsigned _seed /* = 42 */)
    {
        mean_rewards = _mean_rewards;
        transitions = _transitions;
        randgen.set_seed(_seed);
        id = "FiniteMDP";
        reset();
    }

    int FiniteMDP::reset()
    {
        state = 0;
        return 0;
    }

    StepResult<int> FiniteMDP::step(int action)
    {
        // Sample next state
        int next_state = randgen.choice(transitions[state][action]);
        double reward = mean_rewards[state][action][next_state];
        bool done = false;
        StepResult<int> step(next_state, reward, done);
        return step;
    }
}
#endif
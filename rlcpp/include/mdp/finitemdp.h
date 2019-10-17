#ifndef __FINITEMDP_H__
#define __FINITEMDP_H__

/**
 * @file
 * @brief Base class for finite MDPs.
 */

#include <vector>
#include <assert.h> 
#include "mdp.h"
#include "utils.h"

namespace mdp
{
    class FiniteMDP: public MDP<int, int>
    {
    protected:
        /**
         * @brief Default constructor. Returns a undefined MDP.
         */ 
        FiniteMDP(){};

        /**
         * @param _mean_rewards
         * @param _transitions
         * @param _default_state index of the default state
         * @param _seed random seed
         */       
        void set_params(utils::vec_3d _mean_rewards, utils::vec_3d _transitions, int _default_state = 0, unsigned _seed = 42);

        /**
         * @param _mean_rewards
         * @param _transitions
         * @param _terminal_states vector containing the indices of the terminal states
         * @param _default_state index of the default state
         * @param _seed random seed
         */
        void set_params(utils::vec_3d _mean_rewards, utils::vec_3d _transitions, std::vector<int> _terminal_states, int _default_state = 0, unsigned _seed = 42);

    public:

        /**
         * @note The _seed is used for generating the transitions. The state and action spaces have their own (default) seeds.
         * @param _mean_rewards
         * @param _transitions
         * @param _default_state index of the default state
         * @param _seed random seed
         */
        FiniteMDP(utils::vec_3d _mean_rewards, utils::vec_3d _transitions, int _default_state = 0, unsigned _seed = 42);


        /**
         * @note The _seed is used for generating the transitions. The state and action spaces have their own (default) seeds.
         * @param _mean_rewards
         * @param _transitions
         * @param _terminal_states vector containing the indices of the terminal states
         * @param _default_state index of the default state
         * @param _seed random seed
         */
        FiniteMDP(utils::vec_3d _mean_rewards, utils::vec_3d _transitions, std::vector<int> _terminal_states, int _default_state = 0, unsigned _seed = 42);

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
         * Default state
         */
        int default_state;

        /**
         * For random number generation
         */
        utils::Random randgen;

        /**
         * Number of states
         */
        int ns;

        /**
         * Number of actions;
         */
        int na;

        /**
         * Vector of terminal states
         */
        std::vector<int> terminal_states;

        /**
         * State (observation) space
         */ 
        spaces::Discrete observation_space;

        /**
         *  Action space
         */
        spaces::Discrete action_space;

        /**
         * @brief Check if _state is terminal
         * @param _state 
         * @return true if _state is terminal, false otherwise
         */
        bool is_terminal(int _state);

        // Members of base class
        int state;
        std::string id; 
        int reset();
        StepResult<int> step(int action);
    };  
}
#endif
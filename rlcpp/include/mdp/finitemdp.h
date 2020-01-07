#ifndef __FINITEMDP_H__
#define __FINITEMDP_H__

/**
 * @file
 * @brief Base class for finite MDPs.
 */

#include <vector>
#include <string>
#include <assert.h>
#include "abstractmdp.h"
#include "utils.h"
#include "history.h"


namespace mdp
{
    /**
     * Base class for Finite Markov Decision Processes.
     */ 
    class FiniteMDP: public MDP<int, int>
    {

    public:
        /**
         * @param _mean_rewards
         * @param _transitions
         * @param _default_state index of the default state
         * @param _seed random seed
         */
        FiniteMDP(utils::vec::vec_3d _mean_rewards, utils::vec::vec_3d _transitions, int _default_state = 0, int _seed = -1);


        /**
         * @param _mean_rewards
         * @param _transitions
         * @param _terminal_states vector containing the indices of the terminal states
         * @param _default_state index of the default state
         * @param _seed random seed
         */
        FiniteMDP(utils::vec::vec_3d _mean_rewards, utils::vec::vec_3d _transitions, std::vector<int> _terminal_states, int _default_state = 0, int _seed = -1);

        ~FiniteMDP(){};

        /**
         * @brief Set MDP to default_state
         * @return default_state
         */
        int reset();

        /**
         * @brief take a step in the MDP
         * @param action action to take
         * @return StepResult object, contaning next state, reward and 'done' flag
         */
        StepResult<int> step(int action);

        /**
         * @brief Check if _state is terminal
         * @param _state
         * @return true if _state is terminal, false otherwise
         */
        bool is_terminal(int _state);

    protected:
        /**
         * @brief Default constructor. Returns a undefined MDP.
         */
        FiniteMDP(){};

        /**
         * @brief Constructor *without* terminal states.
         * @param _mean_rewards
         * @param _transitions
         * @param _default_state index of the default state
         * @param _seed random seed. If seed < 1, a random seed is selected by calling std::rand().
         */
        void set_params(utils::vec::vec_3d _mean_rewards, utils::vec::vec_3d _transitions, int _default_state = 0, int _seed = -1);

        /**
         * @brief Constructor *with* terminal states.
         * @param _mean_rewards
         * @param _transitions
         * @param _terminal_states vector containing the indices of the terminal states
         * @param _default_state index of the default state
         * @param _seed random seed. If seed < 1, a random seed is selected by calling std::rand().
         */
        void set_params(utils::vec::vec_3d _mean_rewards, utils::vec::vec_3d _transitions, std::vector<int> _terminal_states, int _default_state = 0, int _seed = -1);

        /**
         * @brief check if attributes are well defined.
         */
        void check();
    public:
        /**
         * 3d vector such that mean_rewards[s][a][s'] is the mean reward obtained when the
         * state s' is reached by taking action a in state s.
         */
        utils::vec::vec_3d mean_rewards;

        /**
         * 3d vector such that transitions[s][a][s'] is the probability of reaching
         * state s' by taking action a in state s.
         */
        utils::vec::vec_3d transitions;

        /**
         * Default state
         */
        int default_state;

        /**
         * For random number generation
         */
        utils::rand::Random randgen;

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
         * Object to store history of calls to step().
         * @note This object needs to be manually initialized by the user.
         */
        History<int, int> history;

        // Members of base class

        /**
         * Current state
         */
        int state;
        /**
         * MDP identifier
         */
        std::string id;
    };
}
#endif

#include <algorithm>
#include "finitemdp.h"

namespace mdp
{
    FiniteMDP::FiniteMDP(utils::vec_3d _mean_rewards, utils::vec_3d _transitions, int _default_state /* = 0 */, unsigned _seed /* = 42 */)
    {
        mean_rewards = _mean_rewards;
        transitions = _transitions;
        randgen.set_seed(_seed);
        id = "FiniteMDP";
        default_state = _default_state;

        ns = _mean_rewards.size();
        assert( ns > 0 && "At least one state is required.");
        na = _mean_rewards[0].size();

        observation_space.set_n(ns);
        action_space.set_n(na);

        reset();
    }

    FiniteMDP::FiniteMDP(utils::vec_3d _mean_rewards, utils::vec_3d _transitions, std::vector<int> _terminal_states, int _default_state /* = 0 */, unsigned _seed /* = 42 */)
    {
        mean_rewards = _mean_rewards;
        transitions = _transitions;
        randgen.set_seed(_seed);
        id = "FiniteMDP";
        default_state = _default_state;

        ns = _mean_rewards.size();
        assert( ns > 0 && "At least one state is required.");
        na = _mean_rewards[0].size();

        observation_space.set_n(ns);
        action_space.set_n(na);

        terminal_states = _terminal_states;
        reset();        
    }

    int FiniteMDP::reset()
    {
        state = default_state;
        return default_state;
    }

    bool FiniteMDP::is_terminal(int _state)
    {
        return (std::find(terminal_states.begin(), terminal_states.end(), _state) != terminal_states.end());
    }

    /**
     *  @note done is true if next_state is terminal.
     */
    StepResult<int> FiniteMDP::step(int action)
    {
        // Sample next state
        int next_state = randgen.choice(transitions[state][action]);
        double reward = mean_rewards[state][action][next_state];
        bool done = is_terminal(next_state);
        StepResult<int> step_result(next_state, reward, done);
        state = step_result.next_state;
        return step_result;
    }
}
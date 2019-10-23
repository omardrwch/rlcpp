#include <algorithm>
#include <cmath>
#include "finitemdp.h"

namespace mdp
{
    FiniteMDP::FiniteMDP(utils::vec::vec_3d _mean_rewards, utils::vec::vec_3d _transitions, int _default_state /* = 0 */, int _seed /* = 42 */)
    {
        set_params(_mean_rewards, _transitions, _default_state, _seed);
    }

    FiniteMDP::FiniteMDP(utils::vec::vec_3d _mean_rewards, utils::vec::vec_3d _transitions, std::vector<int> _terminal_states, int _default_state /* = 0 */, int _seed /* = 42 */)
    {
        set_params(_mean_rewards, _transitions, _terminal_states, _default_state, _seed);
    }

    void FiniteMDP::set_params(utils::vec::vec_3d _mean_rewards, utils::vec::vec_3d _transitions, int _default_state /* = 0 */, int _seed /* = 42 */)
    {
      if (_seed < 1) {
        _seed = std::rand();
        std::cout << _seed << std::endl;
      }

        mean_rewards = _mean_rewards;
        transitions = _transitions;
        randgen.set_seed(_seed);
        id = "FiniteMDP";
        default_state = _default_state;

        check();
        ns = _mean_rewards.size();
        na = _mean_rewards[0].size();

        // observation and action spaces
        observation_space.set_n(ns);
        action_space.set_n(na);
        // seeds for spaces
        observation_space.generator.seed(_seed+123);
        action_space.generator.seed(_seed+456);

        reset();
    }

    void FiniteMDP::set_params(utils::vec::vec_3d _mean_rewards, utils::vec::vec_3d _transitions, std::vector<int> _terminal_states, int _default_state /* = 0 */, int _seed /* = 42 */)
    {
      if (_seed < 1) {
        _seed = std::rand();
        std::cout << _seed << std::endl;
      }

        mean_rewards = _mean_rewards;
        transitions = _transitions;
        randgen.set_seed(_seed);
        id = "FiniteMDP";
        default_state = _default_state;

        check();
        ns = _mean_rewards.size();
        na = _mean_rewards[0].size();

        // observation and action spaces
        observation_space.set_n(ns);
        action_space.set_n(na);
        // seeds for spaces
        observation_space.generator.seed(_seed+123);
        action_space.generator.seed(_seed+456);

        terminal_states = _terminal_states;
        reset();
    }

    void FiniteMDP::check()
    {
        // Check shape of transitions and rewards
        assert(mean_rewards.size() > 0);
        assert(mean_rewards[0].size() > 0);
        assert(mean_rewards[0][0].size() > 0);
        assert(transitions.size() > 0);
        assert(transitions[0].size() > 0);
        assert(transitions[0][0].size() > 0);

        // Check consistency of number of states
        assert(mean_rewards[0][0].size() == mean_rewards.size());
        assert(transitions[0][0].size() == transitions.size());
        assert(transitions.size() == mean_rewards.size());

        // Check consistency of number of actions
        assert(mean_rewards[0].size() == transitions[0].size());

        // Check transition probabilities
        for(int i = 0; i < transitions.size(); i++)
        {
            for(int a = 0; a < transitions[0].size(); a++)
            {
                double sum = 0;
                for(int j = 0; j < transitions[0][0].size(); j++)
                {
                    assert(transitions[i][a][j] >= 0.0);
                    sum += transitions[i][a][j];
                }
                assert(std::abs(sum - 1.0) <= 1e-16);
            }
        }
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

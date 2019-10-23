#include <assert.h>
#include <cmath>
#include <algorithm>
#include "mountaincar.h"
#include "utils.h"


namespace mdp
{
MountainCar::MountainCar()
{
    int _seed = std::rand();
    randgen.set_seed(_seed);
    // observation and action spaces
    std::vector<double> _low = {-1.2, -0.07};
    std::vector<double> _high = {0.6, 0.07};
    observation_space.set_bounds(_low, _high);
    action_space.set_n(3);
    // seeds for spaces
    observation_space.generator.seed(_seed+123);
    action_space.generator.seed(_seed+456);

    goal_position = 0.5;
    goal_velocity = 0;

    state.push_back(0);
    state.push_back(0);
}

std::vector<double> MountainCar::reset()
{
    state[position] = randgen.sample_real_uniform(observation_space.low[position], observation_space.high[position]);
    state[velocity] = 0;
    return state;
}

StepResult<std::vector<double>> MountainCar::step(int action)
{
    assert(action_space.contains(action));

    std::vector<double>& lo = observation_space.low;
    std::vector<double>& hi = observation_space.high;

    double p = state[position];
    double v = state[velocity];

    v += (action-1)*force + cos(3*p)*(-gravity);
    v = utils::clamp(v, lo[velocity], hi[velocity]);
    p += v;
    p = utils::clamp(p, lo[position], hi[position]);
    if ((abs(p-lo[position])<1e-10) && (v<0)) v = 0;

    bool done = is_terminal(state);
    double reward = -1;
    if (done) reward = 0;

    state[position] = p;
    state[velocity] = v;

    StepResult<std::vector<double>> step_result(state, reward, done);
    return step_result;
}

bool MountainCar::is_terminal(std::vector<double> state)
{
    return ((state[position] >= goal_position) && (state[velocity]>=goal_velocity));
}
}

#ifndef __MOUNTAINCAR_H__
#define __MOUNTAINCAR_H__

#include <vector>
#include <assert.h>
#include "abstractmdp.h"
#include "continuousmdp.h"
#include "utils.h"
#include "history.h"

namespace mdp
{
class MountainCar: public ContinuousMDP
{
public:
    enum StateLabel
    {
        position = 0, velocity = 1
    };

    MountainCar();
    std::vector<double> reset();
    StepResult<std::vector<double>> step(int action);

protected:
    bool is_terminal(std::vector<double> state);
    double goal_position;
    double goal_velocity;

private:
    static constexpr double force = 0.001;
    static constexpr double gravity = 0.0025;

};
}

#endif

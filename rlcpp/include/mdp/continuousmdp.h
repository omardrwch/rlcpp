#ifndef __CONTINUOUSMDP_H__
#define __CONTINUOUSMDP_H__

#include <vector>
#include <assert.h>
#include "abstractmdp.h"
#include "utils.h"
#include "history.h"

namespace mdp
{
class ContinuousMDP: public MDP<std::vector<double>, int>
{
public:
    ContinuousMDP() {}
    ~ContinuousMDP() {};

    virtual std::vector<double> reset() = 0;
    virtual StepResult<std::vector<double>> step(int action) = 0;

    /**
    * State (observation) space
    */
    spaces::Box observation_space;

    /**
    *  Action space
    */
    spaces::Discrete action_space;

    /**
    * For random number generation
    */
    utils::rand::Random randgen;

    /**
    * Object to store history of calls to step().
    * @note This object needs to be manually initialized by the user.
    */
    History<std::vector<double>, int> history;

    // Members of base class
    int na;
    /**
    * MDP identifier
    */
    std::string id;

    /**
    * Current state
    */
    std::vector<double> state;
};
}

#endif

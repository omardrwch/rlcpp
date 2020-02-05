#ifndef __ABSTRACTMDP_H__
#define __ABSTRACTMDP_H__

#include<string>
#include "space.h"

/**
 * @file
 * @brief Contains abstract class for MDPs
 */


namespace mdp
{
/**
 * @brief Class to represent an object returned by MDP::step()
 */
template<typename S>
class StepResult
{
public:
    StepResult(); // default constructor
    /**
     * @brief Initialize object with data
     * @param _next_state
     * @param _reward
     * @param _done
     */
    StepResult(S _next_state, double _reward, bool _done);
    ~StepResult() {};

    /**
     * @brief Next state
     */
    S next_state;

    /**
     * @brief Value of the reward
     */
    double reward;

    /**
     * @brief Flag that is true if a terminal state is reached
     */
    bool done;
};

template<typename S>
StepResult<S>::StepResult()
{
    next_state = -1;
    reward = 0;
    done = false;
}

template<typename S>
StepResult<S>::StepResult(S _next_state, double _reward, bool _done)
{
    next_state = _next_state;
    reward = _reward;
    done = _done;
}

/**
 * @brief Abstract class for MDPs
 */
template <typename S, typename A>
class MDP
{
public:
    MDP(/* args */) {};
    ~MDP() {};

    /**
     * @brief Put MDP in default state
     * @return Default state
     */
    virtual S reset()=0;

    /**
     * @brief Take a step in the MDP
     * @param action
     * @return An instance of mdp::StepResult containing the next state,
     * the reward and the done flag.
     */
    virtual StepResult<S> step(A action)=0;

    /**
     * Current state
     */
    S state;

    /**
     *  MDP identifier
     */
    std::string id;

    /**
     * Observation space
     */
    spaces::Space<S> observation_space;

     /**
     * Observation space
     */   
    spaces::Space<A> action_space;

};
}

#endif
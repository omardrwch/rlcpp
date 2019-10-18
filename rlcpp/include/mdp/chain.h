#ifndef __CHAIN_H__
#define __CHAIN_H__

/**
 * @file 
 * @brief Define a N-Chain MDP.
 */

#include <vector>
#include <algorithm>
#include "finitemdp.h"
#include "utils.h"

namespace mdp
{
    /**
     * @brief N-Chain environment. States = {0, ..., N-1}, Actions = {0, 1}.
     * @details In state I, when action 0 is taken, the next state is min(I+1, N-1).
     *                      when action 1 is taken, the next state is max(I-1, 0).
     *          A reward of 1 is obtained when the next state is N-1.
     * @param N length of the chain.            
     */ 
    class Chain: public FiniteMDP
    {
    public:
        Chain(int N);
        ~Chain(){};
    };
}


#endif
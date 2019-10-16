#ifndef __FINITEMDP_H__
#define __FINITEMDP_H__

/**
 * @file
 * @brief Base class for finite MDPs.
 */

#include "mdp.h"

namespace mdp
{
   class FiniteMDP: public MDP<int, int>
    {
    public:
        FiniteMDP(/* args */);
        ~FiniteMDP();
    };

    FiniteMDP::FiniteMDP(/* args */)
    {
    }

    FiniteMDP::~FiniteMDP()
    {
    }
}



#endif
#ifndef __EPISODICVI_H__
#define __EPISODICVI_H__

#include "abstractmdp.h"
#include "finitemdp.h"
#include "chain.h"
#include "space.h"
#include "history.h"

namespace mdp
{
    /**
     * @brief Class to run episodic value iteration in a finite MDP.
     */
    class EpisodicVI
    {
        public:
            /**
             * @param mdp FiniteMDP object
             * @param horizon
             */
            EpisodicVI(FiniteMDP& mdp, int horizon);

            /**
             * @brief Run value iteration to find optimal value function. 
             * @details Store results in greedy_policy, V and Q.
             */
            void run();

            /**
             * @brief Run value iteration to find the value of a policy pi.
             * @param pi vector of integers of dimensions (horizon x ns). 
             * @param Vpi vector of doubles, filled with zeros, of dimensions (horizon+1, ns), in which the result is stored.
             */
            void evaluate_policy(utils::vec::ivec_2d pi, utils::vec::vec_2d& Vpi);
        protected:
            /**
             * MDP object.
             */
            FiniteMDP& mdp;
            /**
             * Horizon H.
             */
            int horizon;

        public:
            /**
             * Greedy policy, stored as a vector of integers of dimensions (horizon x ns)
             */
            utils::vec::ivec_2d greedy_policy;
            /**
             * Value function. Dimensions (horizon+1 x ns).
             */
            utils::vec::vec_2d V;

            /**
             * Q function. Dimensions (horizon+1 x ns x na).
             */ 
            utils::vec::vec_3d Q;
    };
}

#endif

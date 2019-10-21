#ifndef __EPISODICVI_H__
#define __EPISODICVI_H__

#include "abstractmdp.h"
#include "finitemdp.h"
#include "chain.h"
#include "space.h"
#include "history.h"

namespace mdp
{
        class EpisodicVI
        {
                public:
                        EpisodicVI(FiniteMDP& mdp, int horizon);

                        void run();

                protected:
                        FiniteMDP& mdp;
                        int horizon;

                public:
                        utils::vec::vec_3d Q;
                        utils::vec::ivec_2d greedy_policy;
                        utils::vec::vec_2d V;

        };
}

#endif

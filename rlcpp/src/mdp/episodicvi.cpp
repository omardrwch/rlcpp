#include <algorithm>
#include <cmath>
#include "episodicvi.h"

namespace mdp
{
EpisodicVI::EpisodicVI(FiniteMDP& mdp, int horizon) :
    mdp(mdp), horizon(horizon)
{
}


void EpisodicVI::run()
{
    Q = utils::vec::get_zeros_3d(horizon + 1, mdp.ns, mdp.na);
    greedy_policy = utils::vec::get_zeros_i2d(horizon, mdp.ns);
    V = utils::vec::get_zeros_2d(horizon + 1, mdp.ns);

    utils::vec::vec_3d& P = mdp.transitions;
    utils::vec::vec_3d& R = mdp.mean_rewards;
    double tmp;

    for(int h=horizon-1; h>=0; h--)
    {
        for (int s=0; s < mdp.ns; s++)
        {
            for (int a=0; a < mdp.na; a++)
            {
                tmp = 0;
                for (int sn=0; sn < mdp.ns; sn++)
                {
                    tmp +=  P[s][a][sn] *(R[s][a][sn] + V[h+1][sn]);
                }
                Q[h][s][a] = tmp;

                if ((a ==0) || (tmp > V[h][s]))
                    V[h][s] = tmp;
                greedy_policy[h][s] = a;

            }
        }
    }
}

void EpisodicVI::evaluate_policy(utils::vec::ivec_2d pi, utils::vec::vec_2d& Vpi)
{
    utils::vec::vec_3d& P = mdp.transitions;
    utils::vec::vec_3d& R = mdp.mean_rewards;

    for (int s=0; s < mdp.ns; ++s) Vpi[horizon][s] = 0;

    for(int h=horizon-1; h>=0; h--)
    {
        for (int s=0; s < mdp.ns; s++)
        {
            int a = pi[h][s];
            double tmp = 0;
            for (int sn=0; sn < mdp.ns; sn++)
            {
                tmp +=  P[s][a][sn] *(R[s][a][sn] + Vpi[h+1][sn]);
            }

            V[h][s] = tmp;
        }
    }

}
}

#ifndef __UCBVI_H__
#define __UCBVI_H__

#include "abstractmdp.h"
#include "finitemdp.h"
#include "episodicvi.h"

namespace online
{
class UCBVI
{
public:
    UCBVI(mdp::FiniteMDP& mdp, int horizon, double scale_factor=1);

    void reset();

    void get_optimistic_q();

    void compute_bonus();

    int run_episode(utils::vec::vec_2d& trueV);

    void update(int state, int action, double reward, int next_state);

protected:
    mdp::FiniteMDP& mdp;
    int horizon, t, episode;
    double delta;

public:
    utils::vec::vec_3d Phat;
    utils::vec::vec_3d Rhat;
    utils::vec::vec_3d Q;
    utils::vec::vec_2d V;
    utils::vec::vec_2d Vpi;
    utils::vec::vec_3d bonus;
    utils::vec::ivec_2d N_sa;
    utils::vec::ivec_3d N_sas;
    utils::vec::ivec_2d policy;
    std::vector<double> all_episode_rewards;
    std::vector<double> episode_value;
    mdp::EpisodicVI VI;
    double scale_factor;

};
}

#endif

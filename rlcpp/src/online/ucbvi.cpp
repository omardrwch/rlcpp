#include "ucbvi.h"
#include <cmath>

namespace online
{
UCBVI::UCBVI(mdp::FiniteMDP &mdp, int horizon) :
    mdp(mdp), horizon(horizon), VI(mdp::EpisodicVI(mdp, horizon))
{
    reset();
}

void UCBVI::reset()
{
    t = episode = 0;
    Phat = utils::vec::get_zeros_3d(mdp.ns, mdp.na, mdp.ns);
    Rhat = utils::vec::get_zeros_3d(mdp.ns, mdp.na, mdp.ns);
    N_sa = utils::vec::get_zeros_i2d(mdp.ns, mdp.na);
    N_sas = utils::vec::get_zeros_i3d(mdp.ns, mdp.na, mdp.ns);
    bonus = utils::vec::get_zeros_3d(horizon, mdp.ns, mdp.na);


    Q = utils::vec::get_zeros_3d(horizon + 1, mdp.ns, mdp.na);
    policy = utils::vec::get_zeros_i2d(horizon, mdp.ns);
    V = utils::vec::get_zeros_2d(horizon + 1, mdp.ns);
    Vpi = utils::vec::get_zeros_2d(horizon + 1, mdp.ns);

    all_episode_rewards.clear();
    episode_value.clear();
}

void UCBVI::get_optimistic_q()
{
    //initialize stage H+1
    for (int i=0; i < mdp.ns; ++i)
        for (int j=0; j <mdp.na; ++j)
            Q[horizon][i][j] = 0;
    double tmp;

    if (episode > 0)
    {
        compute_bonus();

        for(int h=horizon-1; h>=0; h--)
        {
            for (int s=0; s < mdp.ns; s++)
            {
                for (int a=0; a < mdp.na; a++)
                {
                    tmp = 0;
                    for (int sn=0; sn < mdp.ns; sn++)
                    {
                        tmp +=  Phat[s][a][sn] *(Rhat[s][a][sn] + V[h+1][sn]);
                    }
                    tmp += bonus[h][s][a];
                    Q[h][s][a] = tmp;

                    if ((a == 0) || (tmp > V[h][s]))
                        V[h][s] = std::min((double)horizon, tmp);
                    policy[h][s] = a;

                }
            }
        }
    }
}

utils::vec::vec_3d UCBVI::compute_bonus()
{
    int tt = std::max(1, t);
    double L = log(5 * mdp.ns * mdp.na * tt / delta);

    for (int h=0; h < horizon; ++h)
    {
        for (int s=0; s < mdp.ns; s++)
        {
            for (int a=0; a < mdp.na; a++)
            {
                bonus[h][s][a] = 7 * horizon * L / sqrt(std::max(1, N_sa[s][a]));
            }
        }
    }
}

void UCBVI::run_episode()
{
    double episode_reward = 0;
    int action;
    int state = mdp.reset();
    get_optimistic_q();

    // True value of the greedy policy wrt Q
    VI.evaluate_policy(policy, Vpi);
    episode_value.push_back(Vpi[0][state]);

    // execute policy
    for (int h=0; h < horizon; ++h)
    {
        action = policy[h][state];

        // take step and store state and reward
        mdp::StepResult<int> result = mdp.step(action);
        update(state, action, result.reward, result.next_state);

        episode_reward += result.reward;
        state = result.next_state;

        // update total time
        t += 1;
    }
    episode += 1;
    // store the reward obtained in the episode
    all_episode_rewards.push_back(episode_reward);

}

void UCBVI::update(int state, int action, double reward, int next_state)
{
    int old_n = N_sas[state][action][next_state];
    N_sas[state][action][next_state] += 1;
    N_sa[state][action] += 1;
    // int n_sa = 0;
    // for (int sn=0; sn < mdp.ns; ++sn) n_sa += N_sas[state][action][sn];
    for (int sn=0; sn < mdp.ns; ++sn)
        Phat[state][action][sn] = N_sas[state][action][sn] / N_sa[state][action];

    Rhat[state][action][next_state] = (Rhat[state][action][next_state] * old_n + reward) / (old_n + 1);
}


}

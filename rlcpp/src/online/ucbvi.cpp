#include <cmath>
#include <vector>
#include <string>
#include "ucbvi.h"


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

    /** Initialize MDP history
       - horizon*1000 is a rough estimate of the number of total timesteps (=horizon*number_of_episodes)
       - _n_extra_variables is the number of extra variables to be stored
       - names is a vector of strings contaning the name of each extra variable

       The history is updated in UCBVI::run_episode()

        @todo Implement a function history.clear() and call it here.
    */
    int _n_extra_variables = 2;
    // The first parameter in reserve_mem() does not need to be the exact value, it's just for speedup (it is used for calling vector.reserve()).
    mdp.history.reserve_mem(horizon*1000, _n_extra_variables); 
    
    std::vector<std::string> names = {"extra_var_1", "extra_var_2"};
    mdp.history.set_names(names);
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
                        tmp +=  Phat[s][a][sn] * (Rhat[s][a][sn] + V[h+1][sn]);
                    }
                    tmp += bonus[h][s][a];
                    Q[h][s][a] = tmp;

                    if ((a == 0) || (tmp > V[h][s]))
                    {
                        V[h][s] = std::min((double)horizon, tmp);
                        policy[h][s] = a;
                    }

                }
            }
        }
    }
}

void UCBVI::compute_bonus()
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

int UCBVI::run_episode()
{
    double episode_reward = 0;
    int action;
    int state = mdp.reset();
    int initial_state = state;
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

        // ---
        // Update MDP history
        std::vector<double> extra_vars = {-1.0, -1.0}; // values of extra variables (if needed)
        mdp.history.append(state, action, result.reward, result.next_state, extra_vars, episode);
        // ---   

        episode_reward += result.reward;
        state = result.next_state;

        // update total time
        t += 1;
    }
    episode += 1;
    // store the reward obtained in the episode
    all_episode_rewards.push_back(episode_reward);

    return initial_state;
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

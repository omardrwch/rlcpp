#ifndef __UCBVI_H__
#define __UCBVI_H__

#include "abstractmdp.h"
#include "finitemdp.h"
#include "episodicvi.h"
#include "abstractalgorithm.h"

namespace online
{
/**
 * @brief UCBVI algorithm of Azar et al., 2017 (Minimax Regret Bounds for Reinforcement Learning)
 */
class UCBVI: public Algorithm
{
    public:
        UCBVI(mdp::FiniteMDP& mdp, int horizon,
            double scale_factor=1, std::string b_type="bernstein",
            bool save_history=true);

        /**
         * @brief Reset all variables.
         * @details Set counters and estimates to zero and clear stored data.
         */
        void reset();

        /**
         * @brief Compute optimistic Q function.
         * @details Run optimistic value iteration, store data in Q and V.
         */
        void get_optimistic_q();

        /**
         * @brief Compute Hoeffding exploration bonus.
         * @details
         *      bonus(x, a) = scale_factor* 7 * H * L * sqrt*(1 / #(visits to (x,a)))
         *      where L = log(5*S*A*max(1, #visits to (x,a))/delta)
         */
        void compute_hoeffding_bonus();

        /**
         * @brief Compute Bernstein exploration bonus.
         * @details See Algorithm 4 in [1]
         * [1] Azar et al., 2017. Minimax Regret Bounds for Reinforcement Learning
         */
        void compute_bernstein_bonus(int h,  std::vector<double> Vhp1);

        /**
         * @brief Run one episode
         * @param trueV True value functions. Vector of dimensions (horizon x number of states)
         */
        int run_episode(const utils::vec::vec_2d& trueV);

        /**
         * @brief Update estimates
         * @details Updates the visit counts, the reward estimates and the transition probabilities estimates.
         * Called in function run_episode() after each step.
         * @param state
         * @param action
         * @param reward
         * @param next_state
         */
        void update(int state, int action, double reward, int next_state);

    protected:
        /**
         * MDP used by the algorithm.
         */
        mdp::FiniteMDP& mdp;

        /**
         * Horizon H.
         */
        int horizon;

        /**
         * Total time counter.
         */
        int t; 

        /**
         * Episode counter.
         */
        int episode;

        /**
         * Confidence parameter. Set to 0.1.
         */
        double delta;

    public:
        /**
         * Estimate of transition probabilities. Shape (S, A, S).
         */
        utils::vec::vec_3d Phat;
        /**
         * Estimate of rewards. Shape (S, A, S).
         */
        utils::vec::vec_3d Rhat;
        /**
         * Optimistic Q function. Shape (H+1, S, A).
         */
        utils::vec::vec_3d Q;
        /**
         * Optimistic V function. Shape (H+1, S).
         */
        utils::vec::vec_2d V;
        /**
         * Vector used to store the value of the policy obtained in each episode.
         * Shape (H+1, S)
         */
        utils::vec::vec_2d Vpi;
        /**
         * Exploration bonus. Shape (H, S, A).
         */
        utils::vec::vec_3d bonus;
        /**
         * Number of visits to each state-action pair. Shape (S, A).
         */
        utils::vec::ivec_2d N_sa;
        /**
         * Number of visits to each state-action-next state tuple. Shape (S, A, S).
         */
        utils::vec::ivec_3d N_sas;
        /**
         * Greedy (optimistic) policy, updated after each episode. Shape (H, S).
         */ 
        utils::vec::ivec_2d policy;
        /**
         * Vector containing the rewards in each episode.
         */
        std::vector<double> all_episode_rewards;
        /**
         * Stores Vpi[0][initial_state] in each episode.
         */ 
        std::vector<double> episode_value;
        /**
         * Episodic value iteration object.
         */
        mdp::EpisodicVI VI;
        /**
         * Scale factor for exploration bonuses.
         */
        double scale_factor;
        /**
         * Bound type. Must be either "hoeffding" or "bernstein".
         */
        std::string b_type;

        /**
         * If true, the following variables are saved in mdp.history after each step:
         * (episode, state, action, next_state, reward, regret)
         * The regret is constant in each episode and is equal to (
         *      trueV[0][initial_state] - Vpi[0][initial_state])
         * where Vpi is the value of the policy of the previous episode.
         */
        bool save_history;
    };
}

#endif

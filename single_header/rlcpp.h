#include <algorithm>
#include <assert.h>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <stdlib.h>
#include <string>
#include <vector>
#ifndef __RLCPP_H__
#define __EPISODICVI_H__ 
#ifndef __SPACE_H__
#define __SPACE_H__

/**
 * @file
 * @brief Classes for definining observation and action spaces.
 */

/**
 * @brief Definitions for observation and action spaces.
 */
namespace spaces
{

    /**
     * @brief Possible space names.
     */
    enum spc_name {undefined, discrete, box}; 

    /**
     * @brief Base class for observation and action spaces.
     * 
     */
    template <typename T> 
    class Space
    {
    public:
        Space(/* args */){};
        ~Space(){};
        /**
         * @brief Sample a value of the space with a uniform distribution
         */
        virtual T sample()=0;

        /**
         * @brief Returns true if x belongs to the space, and false otherwise.
         * @param x 
         */
        virtual bool contains(T x)=0;

        /**
         * Name of the space (discrete, box, etc.)
         */
        spc_name name = undefined; 

        /**
         * Random number generator
         */
        std::mt19937 generator;
    };

    /**
     * @brief Class for discrete spaces.
     * Set of possible values = {0, ..., n-1}
     */
    class Discrete: public Space<int>
    {
    public:

        /**
         * @brief Default constructor
         */
        Discrete();

        /**
         * @param _n: Value of n
         * @param _seed: seed for random number generation (default = 42)
         */
        Discrete(int _n, unsigned _seed = 42);
        ~Discrete(){};

        /**
         * Number of elements in the space.
         */
        int n; 

        // Methods

        /**
         * @brief Set the value of n, that defines the discrete space {0, ..., n-1}
         */
        void set_n(int _n);

        // Methods of base class
        int sample();
        bool contains(int x);

        /**
         * Name of the space
         */
        spc_name name = discrete;
    };

    /**
     * @brief Class for box spaces in R^n
     */
    class Box: public Space<std::vector<double>>
    {
    public:

        /**
         * @brief Default constructor
         */
        Box();

        /**
         * @param _low: array contaning the lower bounds of the box
         * @param _high: array containing the upper bounds of the box
         * @param _seed: seed for random number generation (default = 42)
         */
        Box(std::vector<double> _low, std::vector<double> _high, unsigned _seed = 42);
        ~Box(){};

        // Methods
        /**
         * @brief Define the lower and upper bounds of the box
         * @param _low: array contaning the lower bounds of the box
         * @param _high: array containing the upper bounds of the box
         */ 
        void set_bounds(std::vector<double> _low, std::vector<double> _high);

        // Methods of base class
        std::vector<double> sample();
        bool contains(std::vector<double> x);

        /**
         * Name of the space
         */
        spc_name name = box;

        // Attributes

        /**
         * Size of the fox
         */
        int size; 

        /**
         * lower bounds of the box
         */
        std::vector<double> low;

        /**
         * upper bounds of the box
         */
        std::vector<double> high;
    };
}
#endif
#ifndef __ABSTRACTMDP_H__
#define __ABSTRACTMDP_H__

#include<string>

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
};
}

#endif
#ifndef __VECTOR_OP__
#define __VECTOR_OP__

/**
 * @file
 * @brief Common vector operations.
 */

namespace utils
{
    /**
     * Utils for common vector operations.
     */
    namespace vec
    {
        /**
         * @brief Type for 2d vector (double)
         */
        typedef std::vector<std::vector<double>> vec_2d;

        /**
         * @brief Type for 2d vector (integer)
         */
        typedef std::vector<std::vector<int>> ivec_2d;

        /**
         * @brief Type for 3d vector (double)
         */
        typedef std::vector<std::vector<std::vector<double>>> vec_3d;

        /**
         * @brief Type for 3d vector (integer)
         */
        typedef std::vector<std::vector<std::vector<int>>> ivec_3d;

        /**
         * @brief Computes the mean of a vector.
         * @param vec
         * @return mean of vec
         */
        double mean(std::vector<double> vec);

        /**
         * @brief Computes the standard deviation of a vector.
         * @param vec
         * @return standard deviation of vec
         */
        double stdev(std::vector<double> vec);

        /**
         * @brief Computes the inner product between vec1 and vec2
         * @param vec1
         * @param vec2
         * @return inner product
         */
        double inner_prod(std::vector<double> vec1, std::vector<double> vec2);

        /**
         * @brief Print vector
         * @param vec
         */
        template <typename T>
        void printvec(std::vector<T> vec)
        {
            int n = vec.size();
            std::cout << "{";
            for(int i = 0; i < n; i++)
            {
                std::cout << vec[i];
                if (i < n-1){ std::cout << ", ";}
            }
            std::cout << "}" << std::endl;
        }

        /**
         * @brief Print vector of double
         */
        template void printvec<double>(std::vector<double>);
        /**
         * @brief Print vector of int
         */
        template void printvec<int>(std::vector<int>);

        /**
         * @brief Get 2d vector of doubles of dimensions (dim1, dim2) filled with zeros
         * @param dim1
         * @param dim2
         * @return vec_2d with dimensions (dim1, dim2)
         */
        vec_2d get_zeros_2d(int dim1, int dim2);

        /**
         * @brief Get 2d vector of integers of dimensions (dim1, dim2) filled with zeros
         * @param dim1
         * @param dim2
         * @return ivec_2d with dimensions (dim1, dim2)
         */
        ivec_2d get_zeros_i2d(int dim1, int dim2);

        /**
         * @brief Get 3d vector of doubles of dimensions (dim1, dim2, dim3) filled with zeros
         * @param dim1
         * @param dim2
         * @param dim3
         * @return vec_3d with dimensions (dim1, dim2, dim3)
         */
        vec_3d get_zeros_3d(int dim1, int dim2, int dim3);

        /**
         * @brief Get 3d vector of integers of dimensions (dim1, dim2, dim3) filled with zeros
         * @param dim1
         * @param dim2
         * @param dim3
         * @return vec_3d with dimensions (dim1, dim2, dim3)
         */
        ivec_3d get_zeros_i3d(int dim1, int dim2, int dim3);
    }
}

#endif
#ifndef __RANDOM_H__
#define __RANDOM_H__

/**
 * @file
 * @brief Contains class for random number generation.
 */

namespace utils
{
    /**
     * Utils for random number generation.
     */
    namespace rand
    {
        /**
         * @brief Class for random number generation.
         */
        class Random
        {
        public:
            /**
             * @brief Initializes object with given seed.
             * @param _seed
             */
            Random(unsigned _seed = 42);
            ~Random(){};

            /**
             * Seed for the std::mt19937 generator.
             */
            unsigned seed;

            /**
             * @brief Set seed for random number generator
             * @param _seed
             */
            void set_seed(unsigned _seed);
            
            /**
             * Random number generator
             */
            std::mt19937 generator;

            /**
             * continuous uniform distribution in (0, 1)
             */ 
            std::uniform_real_distribution<double> real_unif_dist;       

            /**
             *  standard normal distribution
             */
            std::normal_distribution<double> gaussian_dist;

            /**
             * @brief Sample according to probability vector.
             * @details The parameter prob is passed by reference to avoid copying. It is not changed by the algorithm.
             * @param prob probability vector 
             * @param u (optional) sample from a real uniform distribution in (0, 1)
             * @return integer between 0 and prob.size()-1 according to 
             * the probabilities in prob.
             */
            int choice(std::vector<double>& prob, double u = -1);

            /**
             * @brief Sample from (continuous) uniform distribution in (a, b)
             * @param a 
             * @param b
             * @return sample
             */
            double sample_real_uniform(double a, double b);

            /**
             * @brief Sample from a gaussian distribution with mean mu and variance sigma^2 
             * @param mu mean
             * @param sigma standard deviation
             * @return sample
             */
            double sample_gaussian(double mu, double sigma);
        };
    }
}
#endif
#ifndef __UTILS_H__
#define __UTILS_H__

/**
 * @file 
 * All utils headers.
 */

/**
 * @brief Useful definitions (random number generation, vector operations etc.)
 */
namespace utils
{

    // this should be defined in C++17
    /**
     * @brief Clamp a value between an upper and lower bound. Requires C++17.
     * @param v value to be clampled
     * @param lo lower bound
     * @param hi upper bound
     * @tparam T type of v, lo and hi
     */
    template<class T>
    constexpr const T& clamp( const T& v, const T& lo, const T& hi )
    {
        assert( !(hi < lo) );
        return (v < lo) ? lo : (hi < v) ? hi : v;
    }
}

#endif
#ifndef __HISTORY_H__
#define __HISTORY_H__

/**
 * @file 
 * @brief Tools for storing and exporting MDP history (state, action, reward, next_state).
 */

#include<vector>
#include<string>
#include<assert.h>

namespace mdp
{
    /**
     * @brief Encapsulates std::vector<double>, giving a name to the array.
     * @details Used in the class History to store extra data (of type double) with a 'name' identified to specify 
     * what is the data.
     */
    struct NamedDoubleVec
    {
        /**
         * Name that identifies the data.
         */
        std::string name = " ";
        /**
         * Data
         */
        std::vector<double> data;
    };
    
    /**
     * @tparam S is the type of the state variable;
     * @tparam A is the type of the action variable.
     */
    template <typename S, typename A> 
    class History
    {
    public:
        /**
         * Append transition (with no extra variables).
         * @param _state 
         * @param _action
         * @param _reward
         * @param _next_state
         * @param _episode number of the episode, zero by default.
         */
        void append(S _state, A _action, double _reward, S _next_state, int _episode = 0);
    
        /**
         * Append transition (with extra variables).
         * @param _state 
         * @param _action
         * @param _reward
         * @param _next_state
         * @param _extra_vars vector of doubles of size n_extra_variables
         * @param _episode number of the episode, zero by default.
         */
        void append(S _state, A _action, double _reward, S _next_state, std::vector<double> _extra_vars, int _episode = 0);

        /**
         * @brief Set extra variables names
         * @param names vector of string of size n_extra_variables containing the name of each variable.
         */
        void set_names(std::vector<std::string> names);

        /**
         * @brief Print first N entries in the history
         * @param N number of entries to print
         */
        void print(unsigned int N);

        /**
         * @brief Write csv file with history
         * @param filename example: "myfile.csv"
         */
        void to_csv(std::string filename);

        /**
         * @brief clear all stored data
         */
        void clear();

    private:
        /* data */
    public:
        /**
         * @brief Initialize history object and reserve memory for storing data.
         * @param target_length Expected length of data arrays. Used to reserve memory for vectors.
         * @param _n_extra_variables Number of extra variables (of type double) that are stored in each step of the history.
         * @details target_length is 0 by default, but setting it to the number of expected number of iterations
         * with the MDP is recommended for efficiency.
         */
        History(unsigned int target_length=0, unsigned int _n_extra_variables=0);
        ~History();

        /**
         * Reserve memory
         * @param target_length Expected length of data arrays.
         * @param _n_extra_variables Number of extra variables (of type double) that are stored in each step of the history.
         */
        void reserve_mem(unsigned int target_length=0, unsigned int _n_extra_variables=0);

        /**
         * Amount of data stored
         */
        unsigned int length = 0;

        /**
         * Number of extra variables to store
         */
        unsigned int n_extra_variables;

        /**
         * State history
         */ 
        std::vector<S> states; 

        /**
         * Action history
         */
        std::vector<A> actions; 

        /**
         * Next state history
         */
        std::vector<S> next_states;

        /**
         * Reward history
         */
        std::vector<double> rewards;

        /**
         * Episodes 
         */
        std::vector<int> episodes;

        /**
         * Vector of extra variables
         */
        std::vector<NamedDoubleVec> extra_variables;
    };
    
    template <typename S, typename A> 
    History<S, A>::History(unsigned int target_length /* = 0 */, unsigned int _n_extra_variables /* = 0 */)
    {
        // Reserve memory and set n_extra_variables
        reserve_mem(target_length, _n_extra_variables);
    }
    
    template <typename S, typename A> 
    History<S, A>::~History()
    {
    }

    template <typename S, typename A> 
    void History<S, A>::reserve_mem(unsigned int target_length/* = 0 */, unsigned int _n_extra_variables/* = 0 */)
    {
        n_extra_variables = _n_extra_variables;

        if (_n_extra_variables > 0) extra_variables.resize(_n_extra_variables);

        if (target_length > 0)
        {
            states.reserve(target_length);
            actions.reserve(target_length);
            next_states.reserve(target_length);
            rewards.reserve(target_length);
            episodes.reserve(target_length);
            if (n_extra_variables > 0)
            {
                for(int i = 0; i < _n_extra_variables; i++)
                {
                    extra_variables[i].data.reserve(target_length);
                }
            }
        }
    }

    template <typename S, typename A> 
    void History<S, A>::append(S _state, A _action, double _reward, S _next_state, int _episode /* = 0 */)
    {
        assert( n_extra_variables == 0 && "Extra variables need to be appended too!");
        states.push_back(_state);
        actions.push_back(_action);
        next_states.push_back(_next_state);
        rewards.push_back(_reward);
        episodes.push_back(_episode);
        length += 1;
    }

    template <typename S, typename A> 
    void History<S, A>::append(S _state, A _action, double _reward, S _next_state, std::vector<double> _extra_vars, int _episode /* = 0 */)
    {
        states.push_back(_state);
        actions.push_back(_action);
        next_states.push_back(_next_state);
        rewards.push_back(_reward);
        episodes.push_back(_episode);

        assert( _extra_vars.size() == n_extra_variables && "Check length of _extra_vars!");
        for(int i = 0; i < _extra_vars.size(); i++)
        {
            extra_variables[i].data.push_back(_extra_vars[i]); 
        }    
        length += 1;
    }

    template <typename S, typename A> 
    void History<S, A>::set_names(std::vector<std::string> names)
    {
        assert( names.size() == n_extra_variables && "Check length of names!");
        for(int i = 0; i < names.size(); i++)
        {
            extra_variables[i].name = names[i];
        }
    }

    template <typename S, typename A> 
    void History<S, A>::clear()
    {
        states.clear();
        actions.clear();
        next_states.clear();
        rewards.clear();
        episodes.clear();
        if (n_extra_variables > 0)
        {
            for(int i = 0; i < n_extra_variables; i++)
            {
                extra_variables[i].data.clear();
            }
        }
        length = 0;
    }
}

#endif
#ifndef __FINITEMDP_H__
#define __FINITEMDP_H__

/**
 * @file
 * @brief Base class for finite MDPs.
 */

namespace mdp
{
    /**
     * Base class for Finite Markov Decision Processes.
     */ 
    class FiniteMDP: public MDP<int, int>
    {
    protected:
        /**
         * @brief Default constructor. Returns a undefined MDP.
         */
        FiniteMDP(){};

        /**
         * @brief Constructor *without* terminal states.
         * @param _mean_rewards
         * @param _transitions
         * @param _default_state index of the default state
         * @param _seed random seed. If seed < 1, a random seed is selected by calling std::rand().
         */
        void set_params(utils::vec::vec_3d _mean_rewards, utils::vec::vec_3d _transitions, int _default_state = 0, int _seed = -1);

        /**
         * @brief Constructor *with* terminal states.
         * @param _mean_rewards
         * @param _transitions
         * @param _terminal_states vector containing the indices of the terminal states
         * @param _default_state index of the default state
         * @param _seed random seed. If seed < 1, a random seed is selected by calling std::rand().
         */
        void set_params(utils::vec::vec_3d _mean_rewards, utils::vec::vec_3d _transitions, std::vector<int> _terminal_states, int _default_state = 0, int _seed = -1);

        /**
         * @brief check if attributes are well defined.
         */
        void check();
    public:

        /**
         * @param _mean_rewards
         * @param _transitions
         * @param _default_state index of the default state
         * @param _seed random seed
         */
        FiniteMDP(utils::vec::vec_3d _mean_rewards, utils::vec::vec_3d _transitions, int _default_state = 0, int _seed = -1);

        /**
         * @param _mean_rewards
         * @param _transitions
         * @param _terminal_states vector containing the indices of the terminal states
         * @param _default_state index of the default state
         * @param _seed random seed
         */
        FiniteMDP(utils::vec::vec_3d _mean_rewards, utils::vec::vec_3d _transitions, std::vector<int> _terminal_states, int _default_state = 0, int _seed = -1);

        ~FiniteMDP(){};

        /**
         * 3d vector such that mean_rewards[s][a][s'] is the mean reward obtained when the
         * state s' is reached by taking action a in state s.
         */
        utils::vec::vec_3d mean_rewards;

        /**
         * 3d vector such that transitions[s][a][s'] is the probability of reaching
         * state s' by taking action a in state s.
         */
        utils::vec::vec_3d transitions;

        /**
         * Default state
         */
        int default_state;

        /**
         * For random number generation
         */
        utils::rand::Random randgen;

        /**
         * Number of states
         */
        int ns;

        /**
         * Number of actions;
         */
        int na;

        /**
         * Vector of terminal states
         */
        std::vector<int> terminal_states;

        /**
         * State (observation) space
         */
        spaces::Discrete observation_space;

        /**
         *  Action space
         */
        spaces::Discrete action_space;

        /**
         * @brief Check if _state is terminal
         * @param _state
         * @return true if _state is terminal, false otherwise
         */
        bool is_terminal(int _state);

        /**
         * Object to store history of calls to step().
         * @note This object needs to be manually initialized by the user.
         */
        History<int, int> history;

        // Members of base class

        /**
         * Current state
         */
        int state;
        /**
         * MDP identifier
         */
        std::string id;
        int reset();
        StepResult<int> step(int action);
    };
}
#endif
#ifndef __CHAIN_H__
#define __CHAIN_H__

/**
 * @file
 * @brief Define a N-Chain MDP.
 */

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
        /**
         * @brief Build chain MDP of length N
         */
        Chain(int N, double fail_p=0);
        ~Chain(){};
    };
}

#endif
#ifndef __EPISODICVI_H__
#define __EPISODICVI_H__

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
#ifndef __ABSTRACTALGO_H__
#define __ABSTRACTALGO_H__

namespace online
{
  /**
   * @brief Abstract class for online RL algorithms.
   */
  class Algorithm
  {
  public:
      Algorithm(/* args */){};
      ~Algorithm(){};

      /**
       * @brief Reset algorithm
       */
      virtual void reset()=0;
      /**
       * @brief Run one episode.
       */
      virtual int run_episode()=0;
  };
}
#endif
#ifndef __UCBVI_H__
#define __UCBVI_H__

namespace online
{
/**
 * @brief UCBVI algorithm of Azar et al., 2017 (Minimax Regret Bounds for Reinforcement Learning)
 */
class UCBVI: public Algorithm
{
    public:
        /**
         * @param mdp: environment in which to run UCBVI
         * @param horizon horizon H
         * @param scale_factor factor by which to multiply the exploration bonus
         * @param b_type type of bonus. must be "hoeffding" or "bernstein"
         * @param save_history if true, save transtitions and regret in mdp.history
         */
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
         *      bonus(x, a) = scale_factor* 7 * H * L * sqrt*(1 / (visits to (x,a)))
         *      where L = log(5*S*A*max(1, visits to (x,a))/delta)
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
         */
        int run_episode();

        /**
         * @brief Run one episode
         * @param trueV True value functions. Vector of dimensions (horizon x number of states). 
         * Used to compute the regret.
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
#ifndef __CONTINUOUSMDP_H__
#define __CONTINUOUSMDP_H__

namespace mdp
{
    /**
     * @brief Class for continuous-state MDP with discrete actions.
     * @details The state space is spaces::Box and the action space is spaces::Discrete
     */
    class ContinuousMDP: public MDP<std::vector<double>, int>
    {
    public:
        ContinuousMDP() {}
        ~ContinuousMDP() {};

        virtual std::vector<double> reset() = 0;
        virtual StepResult<std::vector<double>> step(int action) = 0;

        /**
        * State (observation) space
        */
        spaces::Box observation_space;

        /**
        *  Action space
        */
        spaces::Discrete action_space;

        /**
        * For random number generation
        */
        utils::rand::Random randgen;

        /**
        * Object to store history of calls to step().
        * @note This object needs to be manually initialized by the user.
        */
        History<std::vector<double>, int> history;

        // Members of base class
        
        /**
         * Number of actions
         */ 
        int na;
        /**
        * MDP identifier
        */
        std::string id;

        /**
        * Current state
        */
        std::vector<double> state;
    };
}

#endif
#ifndef __MOUNTAINCAR_H__
#define __MOUNTAINCAR_H__

namespace mdp
{
    /**
     * @brief 1d Mountain car environment
     * @details
     *    State space = (position, velocity)
     *                   position: value in [-1.2, 0.6]
     *                   velocity: value in [-0.07, 0.07]
     *    Action space: Discrete(3)
     * 
     *    The initial position is a random number (in the position range). 
     *    The initial velocity is 0.
     * 
     *   Action 0: negative force
     *   Action 1: do nothing
     *   Action 2: positive force
     * 
     *   The terminal state is (goal_position, goal_velocity)
     * 
     *   A reward of -1 is obtained everywhere, except for the terminal state, where the reward is 0.
     */
    class MountainCar: public ContinuousMDP
    {
    public:
        /**
         * Indices of position and velocity in the state vector.
         */
        enum StateLabel
        {
            position = 0, velocity = 1
        };

        MountainCar();
        std::vector<double> reset();
        StepResult<std::vector<double>> step(int action);

    protected:
        /**
         * @brief Returns true if the state is terminal.
         */
        bool is_terminal(std::vector<double> state);
        /**
         * Position at the terminal state
         */
        double goal_position;
        /**
         * Velocity at the terminal state
         */
        double goal_velocity;

    private:
        /**
         * Force magnitude.
         */
        static constexpr double force = 0.001;
        /**
         * Gravity.
         */
        static constexpr double gravity = 0.0025;

    };
}

#endif
#ifndef __GRIDWORLD_H__
#define __GRIDWORLD_H__

/**
 * @file
 * @brief Define a simple and finite grid world. No walls!
 */

namespace mdp
{
    /**
     * Define a GridWorld environment: a nrows x ncols grid in which an agent can take 4 actions:
     * 'left', 'right', 'up' and 'down' 
     * 
     * @details
     *   Actions:
     *           0: left    (col -> col - 1)
     *           1: right   (col -> col + 1)
     *           2: up      (row -> row - 1)
     *           3: down    (row -> row + 1)
     * 
     *   Fail probability:
     * 
     *      With probability fail_p, a random action will be taken instead of the chosen action. Note that, even in
     *      the case of failure, the chosen action can be chosen by chance.
     */
    class GridWorld: public FiniteMDP
    {
    public:
        /**
         * Number of rows.
         */
        int nrows;
        /**
         * Number of columns.
         */ 
        int ncols;

        /**
         * Map state indices to 2d coordinates
         */
        std::map<int, std::vector<int>> index2coord;

        /**
         * Map 2d coordinates to state indices
         */
        std::map<std::vector<int>, int> coord2index;

        /**
         * Get coordinates of next state given the coordinates of a state and an action
         */
        std::vector<int> get_neighbor(std::vector<int> state_coord, int action);

        /**
         * Render (ASCII)
         */ 
        void render();

        /**
         * Visualize values on the grid
         * @param values vector containing values to be shown on the grid (e.g., value functions)
         */
        void render_values(std::vector<double> values);

    private:
        /* data */

    protected:
        /**
         * Default constructor
         */
        GridWorld();

    public:
        /**
         * @param _nrows number of rows
         * @param _ncols number of columns
         * @param fail_p failure probability (default = 0)
         * @param sigma variance of the rewards (default = 0)
         */ 
        GridWorld(int _nrows, int _ncols, double fail_p = 0, double sigma = 0);
        ~GridWorld(){};
    };
    
}

#endif
#ifndef __MDP_H__
#define __MDP_H__

/**
 * @file 
 * All mdp headers.
 */

/**
 * @brief Definitions for Markov Decision Processes
 */
namespace mdp{}

#endif
#ifndef __ONLINE_H__
#define __ONLINE_H__

/**
 * @file 
 * All online headers.
 */

/**
 * @brief Implementation of online reinforcement learning algorithms.
 */
namespace online{}

#endif
namespace online
{
    UCBVI::UCBVI(mdp::FiniteMDP &mdp, int horizon,
                double scale_factor, std::string b_type, bool save_history) :
        mdp(mdp), horizon(horizon), VI(mdp::EpisodicVI(mdp, horizon)),
        scale_factor(scale_factor), b_type(b_type), save_history(save_history)
    {
        reset();
    }

    void UCBVI::reset()
    {
        delta = 0.1;
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

        /* Initialize MDP history
         - horizon*1000 is a rough estimate of the number of total timesteps (=horizon*number_of_episodes)
        - _n_extra_variables is the number of extra variables to be stored
        - names is a vector of strings contaning the name of each extra variable

        The history is updated in UCBVI::run_episode()
        */
        if (save_history)
        {
            if (mdp.history.length > 0) mdp.history.clear();
            std::vector<std::string> names = {"regret"};
            // The first parameter in reserve_mem() does not need to be the exact value, 
            // it's just for speedup (it is used for calling vector.reserve()).
            mdp.history.reserve_mem(horizon*10000, names.size());
            mdp.history.set_names(names);
        }
    }

    void UCBVI::get_optimistic_q()
    {
        //initialize stage H+1
        for (int i=0; i < mdp.ns; ++i)
        {
            V[horizon-1][i] = 0;
            for (int j=0; j <mdp.na; ++j)
                Q[horizon][i][j] = 0;
        }
        double tmp;

        if (episode > 0)
        {
            if (b_type == "hoeffding")
            {
                compute_hoeffding_bonus();
            }

            for(int h=horizon-1; h>=0; h--)
            {
                if (b_type == "bernstein")
                {
                    compute_bernstein_bonus(h, V[std::min(h+1, horizon-1)]);
                }
                for (int s=0; s < mdp.ns; s++)
                {
                    for (int a=0; a < mdp.na; a++)
                    {
                        tmp = 0;
                        for (int sn=0; sn < mdp.ns; sn++)
                        {
                            tmp +=  Phat[s][a][sn] * (Rhat[s][a][sn] + V[h+1][sn]);
                        }
                        // add noise to break ties
                        double noise = 1e-10 * std::rand()/(RAND_MAX + 1u);
                        // std::cout << noise <<std::endl;
                        tmp += bonus[h][s][a] + noise;
                        Q[h][s][a] = tmp;

                        if ((a == 0) || (tmp > V[h][s]))
                        {
                            V[h][s] = tmp;
                            policy[h][s] = a;
                        }

                    }
                    // truncate value function
                    V[h][s] = std::min((double)(horizon - h + 2), V[h][s]);
                }
            }
        }
    }

    void UCBVI::compute_hoeffding_bonus()
    {
        for (int h=0; h < horizon; ++h)
        {
            for (int s=0; s < mdp.ns; s++)
            {
                for (int a=0; a < mdp.na; a++)
                {
                    double L = std::log(5 * mdp.ns * mdp.na * std::max(1, N_sa[s][a]) / delta);
                    bonus[h][s][a] = scale_factor * 7 * horizon * L / sqrt(std::max(1, N_sa[s][a]));
                }
            }
        }
    }

    void UCBVI::compute_bernstein_bonus(int h,  std::vector<double> Vhp1)
    {

        for (int s=0; s < mdp.ns; s++)
        {
            for (int a=0; a < mdp.na; a++)
            {
                double L = std::log(5 * mdp.ns * mdp.na * std::max(1, N_sa[s][a]) / delta);
                double n = std::max(1, N_sa[s][a]);
                double var = 0, mean = 0;
                for (int sn=0; sn < mdp.ns; ++sn)
                {
                    mean += Phat[s][a][sn] * Vhp1[sn];
                }
                for (int sn=0; sn < mdp.ns; ++sn)
                {
                    var += Phat[s][a][sn] * (Vhp1[sn] - mean) * (Vhp1[sn] - mean);
                }
                double T1 = sqrt(8 * L * var / n) + 14 * L * horizon / (3*n);
                double T2 = sqrt(8 * horizon * horizon / n);
                bonus[h][s][a] = scale_factor * (T1 + T2);
            }
        }
    }

    int UCBVI::run_episode()
    {
        utils::vec::vec_2d zeros = utils::vec::get_zeros_2d(horizon, mdp.ns);
        return run_episode(zeros);
    }

    int UCBVI::run_episode(const utils::vec::vec_2d& trueV)
    {
        double episode_reward = 0;
        int action;
        int state = mdp.reset();
        int initial_state = state;
        get_optimistic_q();

        // True value of the greedy policy wrt Q
        VI.evaluate_policy(policy, Vpi);
        episode_value.push_back(Vpi[0][state]);

        std::vector<double> extra_vars = {trueV[0][state] - Vpi[0][state]};

        // execute policy
        for (int h=0; h < horizon; ++h)
        {
            action = policy[h][state];

            // take step and store state and reward
            mdp::StepResult<int> result = mdp.step(action);
            update(state, action, result.reward, result.next_state);

            // ---
            // Update MDP history
            if (save_history)
            {
                mdp.history.append(state, action, result.reward, result.next_state, extra_vars, episode);
            }
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
            Phat[state][action][sn] = ((double) N_sas[state][action][sn]) / N_sa[state][action];

        Rhat[state][action][next_state] = (Rhat[state][action][next_state] * old_n + reward) / (old_n + 1.);
    }

}
namespace mdp
{
    GridWorld::GridWorld(int _nrows, int _ncols, double fail_p /* = 0 */, double sigma /* = 0 */)
    {
        nrows = _nrows;
        ncols = _ncols;
        assert(nrows > 1 && "Invalid number of rows");
        assert(ncols > 1 && "Invalid number of columns");
        assert(sigma >= 0);
        assert(fail_p >= 0.0 && fail_p <= 1.0);

        // Number of states and actions
        int S = ncols*nrows;
        int A = 4;

        // Terminal state
        std::vector<double> goal_coord = { (double) nrows - 1, (double) ncols - 1};
        std::vector<int> _terminal_states = {S - 1};

        // Initialize vectors
        utils::vec::vec_3d _rewards = utils::vec::get_zeros_3d(S, A, S);
        utils::vec::vec_3d _transitions = utils::vec::get_zeros_3d(S, A, S);

        // Build maps between coordinates and indices
        int index = 0;
        for(int rr = 0; rr < nrows; rr++)
        {
            for(int cc = 0; cc < ncols; cc++)
            {
                std::vector<int> coord = {rr, cc};
                coord2index[coord] = index;
                index2coord[index] = coord; 
                index++;
            }
        }

        // Build rewards
        for(int jj = 0; jj < S; jj++)
        {
            std::vector<int>& next_state_coord = index2coord[jj];
            double squared_distance = std::pow( (1.0*next_state_coord[0]-1.0*goal_coord[0])/(nrows-1) , 2)
                                      + std::pow( (1.0*next_state_coord[1]-1.0*goal_coord[1])/(ncols-1), 2);
            double reward = 0;
            if (sigma > 0)
            {
                reward = std::exp(-squared_distance/std::pow(sigma, 2));
            }
            else 
            {
                reward = 1.0*(squared_distance == 0);
            }

            for(int ii = 0; ii < S; ii++)
            {
                for(int aa = 0; aa < A; aa++)
                {
                    // reward depends on the distance between the next state and the goal state.
                    _rewards[ii][aa][jj] = reward;
                }
            }
        }

        // Build transitions
        for(int ii = 0; ii < S; ii++)
        {
            std::vector<int>& state_coord = index2coord[ii];
            for(int aa = 0; aa < A; aa++)
            {
                // Coordinates of the next state
                std::vector<int> next_state_coord = get_neighbor(state_coord, aa);
                int next_state_index = coord2index[next_state_coord];
                _transitions[ii][aa][next_state_index] = 1.0;

                /*
                    Handle the failure case.

                    With probability fail_p, go to another neighbor!
                */
                if (fail_p > 0)
                {
                    for(int bb = 0; bb < A; bb++)
                    {
                        if (bb == aa) continue; 
                        std::vector<int> perturbed_next_state_coord = get_neighbor(state_coord, bb);
                        int perturbed_next_state_index = coord2index[perturbed_next_state_coord];
                        _transitions[ii][aa][next_state_index] -= fail_p/4.0;
                        _transitions[ii][aa][perturbed_next_state_index] += fail_p/4.0;
                    }  
                }             
            }
        }
        // Initialize base class (FiniteMDP)
        set_params(_rewards, _transitions, _terminal_states);
        id = "GridWorld";
    }

    std::vector<int> GridWorld::get_neighbor(std::vector<int> state_coord, int action)
    {
        int neighbor_row = state_coord[0];
        int neighbor_col = state_coord[1];      
        switch(action) 
        {
            // Left
            case 0:
                neighbor_col = std::max(0, state_coord[1] - 1);
                break;
            // Right
            case 1:
                neighbor_col = std::min(ncols-1, state_coord[1] + 1);
                break;
            // Up
            case 2:
                neighbor_row = std::max(0, state_coord[0]-1);
                break;
                // Down
            case 3:
                neighbor_row = std::min(nrows-1, state_coord[0]+1);
                break;
        }
        std::vector<int> neighbor_coord = {neighbor_row, neighbor_col};
        return neighbor_coord;
    }

    void GridWorld::render()
    {
        // std::cout<< "GridWorld" << std::endl;
        for(int ii = 0; ii < ncols; ii ++) std::cout<<"----";
        std::cout << std::endl;
        for (auto const& cell : index2coord) // key = cell.first, value = cell.second
        {
            std::string cell_str = "";
            
            // If state index (cell.first) is in terminal states
            if (std::find(terminal_states.begin(), terminal_states.end(), cell.first) != terminal_states.end())
                cell_str = " x  ";
            
            // If current state
            else if (cell.first == state)
                cell_str = " A  ";
            
            // 
            else 
                cell_str = " o  ";
            
            // Display
            std::cout << cell_str;
            if (cell.second[1] == ncols - 1) 
                std::cout << std::endl;
        }
        for(int ii = 0; ii < ncols; ii ++) std::cout<<"----";
        std::cout << std::endl;
    }

    void GridWorld::render_values(std::vector<double> values)
    {
        for(int ii = 0; ii < ncols; ii ++) std::cout<<"------";
        std::cout << std::endl;
        for (auto const& cell : index2coord) // key = cell.first, value = cell.second
        {
            // Round value
            double value = values[cell.first];
            int ivalue = (int) (100*value);
            value = ivalue/100.0;
            std::cout << std::setw (6)<< value;   
            if (cell.second[1] == ncols - 1) 
                std::cout << std::endl;
        }
        for(int ii = 0; ii < ncols; ii ++) std::cout<<"------";
        std::cout << std::endl;       
    }
}namespace mdp
{
    Chain::Chain(int N, double fail_p)
    {
        assert(N > 0 && "Chain needs at least one state");
        utils::vec::vec_3d _rewards = utils::vec::get_zeros_3d(N, 2, N);
        utils::vec::vec_3d _transitions = utils::vec::get_zeros_3d(N, 2, N);
        std::vector<int> _terminal_states = {N-1};

        for(int state = 0; state < N; state++)
        {
            for(int action = 0; action < 2; action++)
            {
                int next_state = -1;
                // First action: go to the right
                if (action == 0)
                {
                    next_state = std::min(state + 1, N-1);
                }
                // Second action: go to the left
                else if (action == 1)
                {
                    next_state = std::max(state - 1, 0);
                }
                _transitions[state][action][next_state] = 1.0 - fail_p;
                _transitions[state][action][state] += fail_p;
                if (next_state == N-1)
                {
                    _rewards[state][action][next_state] = 1.0;
                }
            }
        }

        set_params(_rewards, _transitions, _terminal_states);
        id = "Chain";
    }
}
namespace mdp
{
    FiniteMDP::FiniteMDP(utils::vec::vec_3d _mean_rewards, utils::vec::vec_3d _transitions, int _default_state /* = 0 */, int _seed /* = 42 */)
    {
        set_params(_mean_rewards, _transitions, _default_state, _seed);
    }

    FiniteMDP::FiniteMDP(utils::vec::vec_3d _mean_rewards, utils::vec::vec_3d _transitions, std::vector<int> _terminal_states, int _default_state /* = 0 */, int _seed /* = 42 */)
    {
        set_params(_mean_rewards, _transitions, _terminal_states, _default_state, _seed);
    }

    void FiniteMDP::set_params(utils::vec::vec_3d _mean_rewards, utils::vec::vec_3d _transitions, int _default_state /* = 0 */, int _seed /* = 42 */)
    {
        if (_seed < 1) 
        {
            _seed = std::rand();
            // std::cout << _seed << std::endl;
        }

        mean_rewards = _mean_rewards;
        transitions = _transitions;
        randgen.set_seed(_seed);
        id = "FiniteMDP";
        default_state = _default_state;

        check();
        ns = _mean_rewards.size();
        na = _mean_rewards[0].size();

        // observation and action spaces
        observation_space.set_n(ns);
        action_space.set_n(na);
        // seeds for spaces
        observation_space.generator.seed(_seed+123);
        action_space.generator.seed(_seed+456);

        reset();
    }

    void FiniteMDP::set_params(utils::vec::vec_3d _mean_rewards, utils::vec::vec_3d _transitions, std::vector<int> _terminal_states, int _default_state /* = 0 */, int _seed /* = 42 */)
    {
        if (_seed < 1) 
        {
            _seed = std::rand();
            // std::cout << _seed << std::endl;
        }

        mean_rewards = _mean_rewards;
        transitions = _transitions;
        randgen.set_seed(_seed);
        id = "FiniteMDP";
        default_state = _default_state;

        check();
        ns = _mean_rewards.size();
        na = _mean_rewards[0].size();

        // observation and action spaces
        observation_space.set_n(ns);
        action_space.set_n(na);
        // seeds for spaces
        observation_space.generator.seed(_seed+123);
        action_space.generator.seed(_seed+456);

        terminal_states = _terminal_states;
        reset();
    }

    void FiniteMDP::check()
    {
        // Check shape of transitions and rewards
        assert(mean_rewards.size() > 0);
        assert(mean_rewards[0].size() > 0);
        assert(mean_rewards[0][0].size() > 0);
        assert(transitions.size() > 0);
        assert(transitions[0].size() > 0);
        assert(transitions[0][0].size() > 0);

        // Check consistency of number of states
        assert(mean_rewards[0][0].size() == mean_rewards.size());
        assert(transitions[0][0].size() == transitions.size());
        assert(transitions.size() == mean_rewards.size());

        // Check consistency of number of actions
        assert(mean_rewards[0].size() == transitions[0].size());

        // Check transition probabilities
        for(int i = 0; i < transitions.size(); i++)
        {
            for(int a = 0; a < transitions[0].size(); a++)
            {
                double sum = 0;
                for(int j = 0; j < transitions[0][0].size(); j++)
                {
                    assert(transitions[i][a][j] >= 0.0);
                    sum += transitions[i][a][j];
                }
                // std::cout << std::abs(sum - 1.0) << std::endl;
                assert(std::abs(sum - 1.0) <= 1e-12 && "Probabilities must sum to 1");
            }
        }
    }

    int FiniteMDP::reset()
    {
        state = default_state;
        return default_state;
    }

    bool FiniteMDP::is_terminal(int _state)
    {
        return (std::find(terminal_states.begin(), terminal_states.end(), _state) != terminal_states.end());
    }

    /**
     *  @note done is true if next_state is terminal.
     */
    StepResult<int> FiniteMDP::step(int action)
    {
        // Sample next state
        int next_state = randgen.choice(transitions[state][action]);
        double reward = mean_rewards[state][action][next_state];
        bool done = is_terminal(next_state);
        StepResult<int> step_result(next_state, reward, done);
        state = step_result.next_state;
        return step_result;
    }
}
namespace mdp
{
MountainCar::MountainCar()
{
    int _seed = std::rand();
    randgen.set_seed(_seed);
    // observation and action spaces
    std::vector<double> _low = {-1.2, -0.07};
    std::vector<double> _high = {0.6, 0.07};
    observation_space.set_bounds(_low, _high);
    action_space.set_n(3);
    // seeds for spaces
    observation_space.generator.seed(_seed+123);
    action_space.generator.seed(_seed+456);

    goal_position = 0.5;
    goal_velocity = 0;

    state.push_back(0);
    state.push_back(0);

    id = "MountainCar";
}

std::vector<double> MountainCar::reset()
{
    state[position] = randgen.sample_real_uniform(observation_space.low[position], observation_space.high[position]);
    state[velocity] = 0;
    return state;
}

StepResult<std::vector<double>> MountainCar::step(int action)
{
    assert(action_space.contains(action));

    std::vector<double>& lo = observation_space.low;
    std::vector<double>& hi = observation_space.high;

    double p = state[position];
    double v = state[velocity];

    v += (action-1)*force + std::cos(3*p)*(-gravity);
    v = utils::clamp(v, lo[velocity], hi[velocity]);
    p += v;
    p = utils::clamp(p, lo[position], hi[position]);
    if ((abs(p-lo[position])<1e-10) && (v<0)) v = 0;

    bool done = is_terminal(state);
    double reward = -1;
    if (done) reward = 0;

    state[position] = p;
    state[velocity] = v;

    StepResult<std::vector<double>> step_result(state, reward, done);
    return step_result;
}

bool MountainCar::is_terminal(std::vector<double> state)
{
    return ((state[position] >= goal_position) && (state[velocity]>=goal_velocity));
}
}
namespace utils
{
    namespace vec
    {
        double mean(std::vector<double> vec)
        {
            double result = 0;
            int n = vec.size();
            if (n == 0) {std::cerr << "Warning: calling mean() on empty vector." <<std::endl;}
            for(int i = 0; i < n; i++)
            {
                result += vec[i];
            }
            return result/((double) n);
        }

        double stdev(std::vector<double> vec)
        {
            int n = vec.size();
            if (n == 0) {std::cerr << "Warning: calling stdev() on empty vector." <<std::endl;}
            double mu = mean(vec);
            std::vector<double> aux(n);
            for(int i = 0; i < n; i++)
            {
                aux[i] = std::pow(vec[i]-mu, 2.0);
            }
            return std::sqrt(mean(aux));
        }

        double inner_prod(std::vector<double> vec1, std::vector<double> vec2)
        {
            int n = vec1.size();
            assert( n == vec2.size() && "vec1 and vec2 must have the same size.");
            if (n == 0) {std::cerr << "Warning: calling inner_prod() on empty vectors." <<std::endl;}
            double result = 0.0;
            for(int i = 0; i < n; i++)
            {
                result += vec1[i]*vec2[i];
            }
            return result;
        }

        // template <typename T>
        // void printvec(std::vector<T> vec)
        // {
        //     int n = vec.size();
        //     std::cout << "{";
        //     for(int i = 0; i < n; i++)
        //     {
        //         std::cout << vec[i];
        //         if (i < n-1){ std::cout << ", ";}
        //     }
        //     std::cout << "}" << std::endl;
        // }

        vec_2d get_zeros_2d(int dim1, int dim2)
        {
            utils::vec::vec_2d vector;
            for(int ii = 0; ii < dim1; ii++)
            {
                vector.push_back(std::vector<double>());
                for(int jj = 0; jj < dim2; jj++) vector[ii].push_back(0.0);
            }
            return vector;
        }

        ivec_2d get_zeros_i2d(int dim1, int dim2)
        {
            utils::vec::ivec_2d vector;
            for(int ii = 0; ii < dim1; ii++)
            {
                vector.push_back(std::vector<int>());
                for(int jj = 0; jj < dim2; jj++) vector[ii].push_back(0);
            }
            return vector;
        }

        vec_3d get_zeros_3d(int dim1, int dim2, int dim3)
        {
            utils::vec::vec_3d vector;
            for(int ii = 0; ii < dim1; ii++)
            {
                vector.push_back(std::vector<std::vector<double>>());
                for(int jj = 0; jj < dim2; jj++)
                {
                    vector[ii].push_back(std::vector<double>());
                    for(int kk = 0; kk < dim3; kk++) vector[ii][jj].push_back(0.0);
                }
            }
            return vector;
        }

        ivec_3d get_zeros_i3d(int dim1, int dim2, int dim3)
        {
            utils::vec::ivec_3d vector;
            for(int ii = 0; ii < dim1; ii++)
            {
                vector.push_back(std::vector<std::vector<int>>());
                for(int jj = 0; jj < dim2; jj++)
                {
                    vector[ii].push_back(std::vector<int>());
                    for(int kk = 0; kk < dim3; kk++) vector[ii][jj].push_back(0.0);
                }
            }
            return vector;
        }
    }
}
/*
    Following this answer: https://stackoverflow.com/a/13952386/5691288
*/

namespace mdp
{
    /*
        -----------------------------------------------------------------------------------------------------
        Initialization of History for types <int, int> and related implementations (e.g., used in FiniteMDP).
        -----------------------------------------------------------------------------------------------------
    */
    template class History<int, int>;

    /**
     * @brief Print first N entries of the history.
     * @param N
     */
    template <>
    void History<int, int>::print(unsigned int N)
    {
        int n = std::min(N, length);
        std::cout << std::endl << " -------------- First " << n << " entries of history --------------" << std::endl;
        for(int i = 0; i < n; i ++)
        {
            std::cout << " | "  << "episode = "     << episodes[i] ;
            std::cout << " | "  << "state = "       << states[i] ;
            std::cout << " | "  << "action = "      << actions[i] ;
            std::cout << " | "  << "next state = "  << next_states[i];
            std::cout << " | "  << "reward = "      << rewards[i];
            for(int j = 0; j < n_extra_variables; j++)
            {
                std::cout << " | "  << extra_variables[j].name <<" = "   << extra_variables[j].data[i];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    /**
     * @brief Write history in csv file
     * @param filename example: "myfile.csv"
     */
    template <>
    void History<int, int>::to_csv(std::string filename)
    {
        std::ofstream file;
        file.open (filename);
        file << "episode,state,action,next_state, reward,";
        for(int j = 0; j < n_extra_variables; j++) file << extra_variables[j].name << ",";
        file << "\n";
        for(int i = 0; i < length; i ++)
        {
            file << episodes[i] << ",";
            file << states[i] << ",";
            file << actions[i] << ",";
            file << next_states[i] << ",";
            file << rewards[i] << ",";
            for(int j = 0; j < n_extra_variables; j++)
            {
                file <<  extra_variables[j].data[i] << ",";
            }
            file << "\n";
        }
        file.close();
    }

    /*
        -----------------------------------------------------------------------------------------------------
        Initialization of History for types <std::vector<double>, int> and related implementations (e.g., might be used in
        enviroments with box states and discrete actions)
        -----------------------------------------------------------------------------------------------------
    */
   template class History<std::vector<double>, int>;

   /**
    * @brief Print first N entries of the history.
    * @param N
    */
   template <>
   void History<std::vector<double>, int>::print(unsigned int N)
   {
       int n = std::min(N, length);
       std::cout << std::endl << " -------------- First " << n << " entries of history --------------" << std::endl;
       std::cout << std::setprecision(3);
       std::cout << std::fixed;
       for(int i = 0; i < n; i ++)
       {
           std::cout << " | "  << "episode = "     << episodes[i] ;
           std::cout << " | "  << "state = [";
           for (int k = 0, ke = states[i].size(); k < ke; ++k) {
             std::cout << states[i][k];
             if (k < ke - 1) std::cout << ",";
           }
           std::cout << "]";
           std::cout << " | "  << "action = "      << actions[i] ;
           std::cout << " | "  << "next state = [";
           for (int k = 0, ke = next_states[i].size(); k < ke; ++k) {
             std::cout << next_states[i][k];
             if (k < ke - 1) std::cout << ",";
           }
           std::cout << "]";
           std::cout << " | "  << "reward = "      << rewards[i];
           for(int j = 0; j < n_extra_variables; j++)
           {
               std::cout << " | "  << extra_variables[j].name <<" = "   << extra_variables[j].data[i];
           }
           std::cout << std::endl;
       }
       std::cout << std::endl;
       std::cout << std::setprecision(6);
       std::cout.unsetf(std::ios::fixed | std::ios::scientific);
   }
}
namespace utils
{
    namespace rand
    {
        Random::Random(unsigned _seed /* = 42 */)
        {
            seed = _seed;
            generator.seed(_seed);
        }

        void Random::set_seed(unsigned _seed)
        {
            seed = _seed;
            generator.seed(_seed);
        }

        int Random::choice(std::vector<double>& prob, double u /* = -1 */)
        {
            int n = prob.size();
            if (n == 0)
            {
                std::cerr << "Calling Random::choice with empty probability vector! Returning -1." << std::endl;
                return -1;
            }
            std::vector<double> cumul(n);

            // Compute cumulative distribution function 
            cumul[0] = prob[0];
            for(int i = 1; i < n; i++)
            {
                cumul[i] = cumul[i-1] + prob[i];
            }
            // Get sample 
            double unif_sample;
            if (u == -1){ unif_sample = real_unif_dist(generator); }
            else {unif_sample = u;}

            int sample = 0;
            for(int i = 0; i < n; i++)
            {
                if (unif_sample <= cumul[i])
                {
                    return i;
                }
            }
            return -1;  // in case of error
        }

        double Random::sample_real_uniform(double a, double b)
        {
            assert( b >= a && "b must be greater than a");
            double unif_sample = real_unif_dist(generator);
            return (b - a)*unif_sample + a;
        }

        double Random::sample_gaussian(double mu, double sigma)
        {
            assert ( sigma > 0  && "Standard deviation must be positive.");
            double standard_sample = gaussian_dist(generator);
            return mu + sigma*standard_sample;
        }
    }
}namespace spaces
{
    /*
    Members of Discrete
    */ 

   Discrete::Discrete()
   {
       n = 0;
   }

    Discrete::Discrete(int _n, unsigned _seed /* = 42 */) 
    {
        n = _n;
        generator.seed(_seed);
    }

    void Discrete::set_n(int _n)
    {
        n = _n;
    }

    bool Discrete::contains(int x)
    {
        return (x >= 0 && x < n);
    }

    int Discrete::sample()
    {
        std::uniform_int_distribution<int> distribution(0,n-1);
        return distribution(generator);
    }

    /*
    Members of Box
    */
    Box::Box()
    {
        // Do nothing. low and high are empty vectors.
    }

    Box::Box(std::vector<double> _low, std::vector<double> _high, unsigned _seed /* = 42 */)
    {
        low = _low;
        high = _high;
        size = _low.size();
        generator.seed(_seed);
        assert(size == _high.size() && "The size of _low and _high must be the same.");
    }    

    void Box::set_bounds(std::vector<double> _low, std::vector<double> _high)
    {
        low = _low; 
        high = _high;
    }

    bool Box::contains(std::vector<double> x)
    {
        bool contains = true;
        if (x.size() != size)
        {
            contains = false;
        }
        for(int i = 0; i < x.size(); i++)
        {
            contains = contains && (x[i] >= low[i] && x[i] <= high[i]);
        }
        return contains;
    }

    std::vector<double> Box::sample()
    {
        // uniform real distribution
        std::uniform_real_distribution<double> distribution(0.0,1.0);

        std::vector<double> sampled_state(size);
        for(int i = 0; i < size; i++)
        {
           double a;
           double b;
           a = low[i];
           b = high[i];
           sampled_state[i] = a + (b-a)*distribution(generator);
        } 
        return sampled_state;
    }
}namespace mdp
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
                {
                    V[h][s] = tmp;
                    greedy_policy[h][s] = a;
                }

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

            Vpi[h][s] = tmp;
        }
    }

}
}
#endif

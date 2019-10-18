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
        std::string name = " ";
        std::vector<double> data;
    };
    

    /**
     * @tparam S is the type of the state variable;
     * @tparam A is the type of the action variable.
     */
    template <typename S, typename A> 
    class History
    {
    private:
        /* data */
    public:
        /**
         * @brief Initialize history object and reserve memory for storing data.
         * @param target_length Expected length of data arrays. Used to reserve memory for vectors.
         * @param n_extra_variables Number of extra variables (of type double) that are stored in each step of the history.
         * @details target_length is 0 by default, but setting it to the number of expected number of iterations
         * with the MDP is recommended for efficiency.
         */
        History(unsigned int target_length=0, unsigned int _n_extra_variables=0);
        ~History();

        /**
         * Reserve memory
         * @param target_length Expected length of data arrays.
         * @param n_extra_variables Number of extra variables (of type double) that are stored in each step of the history.
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
         */
        void print(unsigned int N);
    };
    

    template <typename S, typename A> 
    History<S, A>::History(unsigned int target_length /* = 0 */, unsigned int _n_extra_variables /* = 0 */)
    {
        n_extra_variables = _n_extra_variables;
        // Reserve memory
        reserve_mem(target_length, _n_extra_variables);
    }
    
    template <typename S, typename A> 
    History<S, A>::~History()
    {
    }

    template <typename S, typename A> 
    void History<S, A>::reserve_mem(unsigned int target_length/* = 0 */, unsigned int _n_extra_variables/* = 0 */)
    {
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
        append(_state, _action, _reward, _next_state, _episode);

        assert( _extra_vars.size() == n_extra_variables && "Check length of _extra_vars!");
        for(int i = 0; i < _extra_vars.size(); i++)
        {
            extra_variables[i].data.push_back(_extra_vars[i]); 
        }    
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

}

#endif
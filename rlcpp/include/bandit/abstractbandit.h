#ifndef __ABSTRACTBANDIT_H__
#define __ABSTRACTBANDIT_H__

/**
 * @file
 * @brief Contains abstract class for bandit problems
 */

namespace bandit
{
    /**
     * @brief Abstract class for bandit problems.
     * @tparam A type of arm (int for finite bandits, double for continuous bandits)
     * @tparam M type of "vector" of means. std::vector<double> for finite bandits, std::function<double(double)> & for continuous bandits
     */
    template <typename A, typename M>
    class Bandit
    {
    private:
        /* data */
    public:
        Bandit(){n_arms = -1;};
        ~Bandit(){};

        /**
         * Pull an arm.
         */
        virtual double sample(A arm) = 0;

        /**
         * Return means
         */
        virtual M get_means() = 0; 

        /**
         * Number of arms
         * @note Set to -1 if infinity or undefined.
         */
        int n_arms;
    };    
}

#endif
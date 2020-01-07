#ifndef __DISCRETE_LIPSCHITZ_BANDIT_H__
#define __DISCRETE_LIPSCHITZ_BANDIT_H__

#include <functional>
#include <vector>
#include "bandit.h"

/**
 * @file
 * @brief Implements a class for a Lipschitz bandit problem with a finite number of arms and Gaussian rewards.
 */ 


namespace bandit
{
    /**
     * @brief Lipschitz bandit problem with a finite number of arms and Gaussian rewards.
     */
    class DiscreteLipschitzBandit
    {
    public:
        /**
         * @param _F a Lipschitz function f(x) that takes a double as input and returns a double.
         * @param _L Lipschitz constant of the function f(x)
         * @param _xvalues vector containing the points [x_1, ..., x_n] such that the means of the n arms are 
         *                 [f(x_1), ..., f(x_n)]
         * @param _seed
         */
        DiscreteLipschitzBandit(const std::function<double(double)> &_F, 
                                double _L,
                                std::vector<double> _xvalues,
                                double _sigma,
                                int _seed = -1);
        ~DiscreteLipschitzBandit(){};

        /**
         * Lipschitz function f(x)
         */
        const std::function<double(double)> *F;

        /**
         * Lipschitz constant of f(x)
         */
        double L;

        /**
         * Vector containing the points [x_1, ..., x_n] such that the means of the n arms are [f(x_1), ..., f(x_n)]
         */
        std::vector<double> xvalues;

        /**
         * Starndard deviation of the Gaussian noise.
         */
        double sigma;

        /**
         * Number of arms
         */
        int n_arms;

        /**
         * Vector containing the mean of each arm.
         */
        std::vector<double> means;

        /**
         * Vector contaning the arms
         */ 
        std::vector<bandit::GaussianArm> arms; 
    };

    DiscreteLipschitzBandit::DiscreteLipschitzBandit(const std::function<double(double)> &_F, 
                                                     double _L,
                                                     std::vector<double> _xvalues,
                                                     double _sigma,
                                                     int _seed /* = -1 */)
    {
        if (_seed < 1) _seed = std::rand();
        F = &_F;
        L = _L; 
        sigma = _sigma;
        xvalues = _xvalues;

        // Setting up the arms
        n_arms = _xvalues.size();

        for(int i = 0; i<= n_arms; i++)
        {
            means.push_back( (*F)(xvalues[i]) );
            arms.push_back(bandit::GaussianArm(means[i], sigma, _seed));
        }   
    }
}


#endif
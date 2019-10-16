#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <random>
#include <vector>

/**
 * @file
 * @brief Contains class for random number generation.
 */

namespace utils
{
    class Random
    {
    public:
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
         * @param prob probability vector
         * @param u (optional) sample from a real uniform distribution in (0, 1)
         * @return integer between 0 and prob.size()-1 according to 
         * the probabilities in prob.
         */
        int choice(std::vector<double> prob, double u = -1);

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
#endif
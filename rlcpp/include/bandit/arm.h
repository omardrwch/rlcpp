#ifndef __ARM_H__
#define __ARM_H__

#include "utils.h"

/**
 * @file
 * @brief Contains classes for defining arms for Multi Armed Bandits problems
 */

namespace bandit
{
    /**
     * Abstract class for Arm
     */
    class Arm
    {
    private:
        /* data */
    public:
        Arm(double _mean, int _seed = 42);
        ~Arm(){};

        /**
         * Return a sample from the arm distribution.
         */
        virtual double sample() = 0;

        /**
         * mean of the arm distribution
         */
        double mean;

        /**
         * Random number generator
         */
        utils::rand::Random randgen; 
    };


    /**
     * Gaussian arm with given mean and variance
     */
    class GaussianArm: public Arm
    {
    private:
        /* data */
    public:
        /**
         * Initialize Gaussian arm with mean mu and variance sigma^2
         * @param _mu
         * @param _sigma
         * @param _seed for random number generation
         */
        GaussianArm(double _mu, double _sigma, int _seed = 42);
        ~GaussianArm(){};

        /**
         * Mean
         */
        double mu;

        /**
         * Standard deviation
         */
        double sigma; 

        /**
         * Sample
         */
        double sample();
    };
}


#endif
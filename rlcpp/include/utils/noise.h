#ifndef __NOISE_H__
#define __NOISE_H__

#include "utils.h"

/**
 * @file
 * @brief Contains classes for generating noise (zero-mean random variables).
 */

namespace utils
{
    /**
     * @brief Utils for generating noise (Gaussian noise etc.) for rewards
     */
    namespace rand
    {
        /**
         * Base class for noise objects.
         */
        class Noise
        {
        public:
            /**
             * Initializes object with a seed
             * @param _seed
             */
            Noise(unsigned _seed = 42);
            /**
             * Initializes object with an instance of Random object
             * @param _randgen instance of Random object
             */
            Noise(Random _randgen);
            ~Noise(){};

            /**
             * Get a sample from noise
             * @note default implementation in base class always returns 0
             * @return noise sample, obtained using randgen
             */
            virtual double sample();

            /**
             * For random number generation
            */
            Random randgen;
        };


        /**
         * Gaussian noise
         */
        class GaussianNoise: public Noise
        {
        public:
            /**
             * Initialize Gaussian noise with given sigma (standard deviation)
             * @param _randgen instance of Random object
             * @param _sigma standard deviation
             */
            GaussianNoise(double _sigma, Random _randgen);

            /**
             * Initialize Gaussian noise with given sigma (standard deviation)
             * @param _seed 
             * @param _sigma standard deviation
             */
            GaussianNoise(double _sigma = 1.0, unsigned _seed = 42);

            ~GaussianNoise(){};

            /**
             * Standard deviation
             */
            double sigma;

            /**
             * Get a sample from noise
             * @return noise sample, obtained using randgen
             */
            double sample();
        };
    }
}

#endif
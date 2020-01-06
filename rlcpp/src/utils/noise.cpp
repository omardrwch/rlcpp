#include "utils.h"
#include "noise.h"

namespace utils
{
    namespace rand
    {

        /* 

            Methods of Noise (base class)

        */
        Noise::Noise(Random _randgen)
        {
            randgen = _randgen;
        }

        Noise::Noise(unsigned _seed /* = 42 */)
        {
            randgen = Random(_seed);
        }

        double Noise::sample()
        {
            return 0;
        }


        /*

            Methods of GaussianNoise

        */
        GaussianNoise::GaussianNoise(double _sigma, Random _randgen): Noise(_randgen)
        {
            sigma = _sigma; 
        }

        GaussianNoise::GaussianNoise(double _sigma /* = 1.0 */, unsigned _seed /* = 42 */): Noise(_seed)
        {
            sigma = _sigma; 
        }

        double GaussianNoise::sample()
        {
            return randgen.sample_gaussian(0, sigma);
        }


    }
}
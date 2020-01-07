#include "arm.h"

namespace bandit
{
    /*

        Base class

    */
    Arm::Arm(double _mean, int _seed /* = 42 */)
    {
        randgen.set_seed(_seed);
        mean = _mean;
    }


    /*

        Gaussian arm

    */

    GaussianArm::GaussianArm(double _mu, double _sigma, int _seed /* = 42 */): Arm(_mu, _seed)
    {
        mean = _mu; 
        mu = _mu;
        sigma = _sigma;
    }

    double GaussianArm::sample()
    {
        return randgen.sample_gaussian(mu, sigma);
    }
}
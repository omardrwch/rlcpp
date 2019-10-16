#include "random.h"
#include <assert.h> 
#include <iostream>

namespace utils
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

    int Random::choice(std::vector<double> prob, double u /* = -1 */)
    {
        int n = prob.size();
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
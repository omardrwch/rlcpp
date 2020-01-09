#include "discrete_lipschitz_bandit.h"


namespace bandit
{
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
        n_arms = xvalues.size();

        for(int i = 0; i<= n_arms; i++)
        {
            means.push_back( (*F)(xvalues[i]) );
            arms.push_back(bandit::GaussianArm(means[i], sigma, _seed));
        }   
    }

    double DiscreteLipschitzBandit::sample(int arm_index)
    {
        return arms[arm_index].sample();
    }
}
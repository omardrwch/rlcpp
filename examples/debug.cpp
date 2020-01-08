/*

    There is nothing important in this file. I use this just to test a few things :)

*/

#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include "space.h"
#include "utils.h"
#include "bandit.h"
#include "mdp.h"

using namespace std;


void test(mdp::DiscreteReward reward_function)
{
    cout << reward_function.noise_type << endl;
}

double f(double x)
{
    return std::sin(x);
}

int main(void)
{
    // int N = 10000;
    // bandit::GaussianArm arm(1.0, 0.1);
    // vector<double> samples(N);

    // for(int i=0; i< N; i++) 
    // {
    //    samples[i] = arm.sample();
    // }

    // cout << "mean = " << utils::vec::mean(samples) << endl;
    // cout << "sigma = " << utils::vec::stdev(samples) << endl;

    // vector<double> xvalues{ 0.1, 0.5, 1.0 };
    // double sigma = 0.01;
    // bandit::DiscreteLipschitzBandit lipschitz_bandit(f, 1, xvalues, sigma);

    // cout << (*lipschitz_bandit.F)(3.1415926535/2) << endl;

    // for(int i = 0; i < xvalues.size(); i++)
    //     cout << lipschitz_bandit.arms[i].sample() << endl;


    int S = 3;
    int A = 2; 
    utils::vec::vec_3d _rewards = utils::vec::get_zeros_3d(S, A, S);
    std::vector<double> noise_params;
    noise_params.push_back(0.1);
    mdp::DiscreteReward reward_function(_rewards, "gaussian", noise_params);
    
    test(reward_function);
    test(_rewards);

    return 0;
}

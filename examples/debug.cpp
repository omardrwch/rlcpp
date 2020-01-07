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

using namespace std;


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

    vector<double> xvalues{ 0.1, 0.5, 1.0 };
    double sigma = 0.01;
    bandit::DiscreteLipschitzBandit lipschitz_bandit(f, 1, xvalues, sigma);

    cout << (*lipschitz_bandit.F)(3.1415926535/2) << endl;

    for(int i = 0; i < xvalues.size(); i++)
        cout << lipschitz_bandit.arms[i].sample() << endl;

    return 0;
}

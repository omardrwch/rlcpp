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

double f(double x)
{
    return std::sin(x);
}

int main(void)
{
    vector<double> xvalues{ 0.1, 0.5, 1.0 };
    double sigma = 0.01;
    bandit::DiscreteLipschitzBandit lipschitz_bandit(f, 1, xvalues, sigma, 42);

    cout << (*lipschitz_bandit.F)(3.1415926535/2) << endl;

    for(int i = 0; i < xvalues.size(); i++)
        cout << lipschitz_bandit.arms[i].sample() << endl;

    return 0;
}

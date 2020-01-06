/*

    There is nothing important in this file. I use this just to test a few things :)

*/

#include <iostream>
#include <random>
#include <vector>
#include "space.h"
#include "utils.h"

using namespace std;

int main(void)
{
    // int N = 1000;
    // vector<double> samples1(N);
    // vector<double> samples2(N);


    // utils::rand::GaussianNoise gnoise(0.1, 123);
    // utils::rand::Noise *noise; 
    // noise = &gnoise; 
    // // utils::rand::Noise noise; 

    // for(int i = 0; i < N; i++)  
    // { 
    //     samples1[i] = (*noise).sample();
    //     samples2[i] = (*noise).sample();
    //     // cout << samples[i] << endl; 
    // }
    // cout << endl << "stdev = " << utils::vec::stdev(samples1) << endl; 
    // cout << endl << "stdev = " << utils::vec::stdev(samples2) << endl; 

    utils::rand::Random randgen(123);

    cout << randgen.sample_gaussian(0, 1) << endl;

    utils::rand::Random second_randgen;
    second_randgen = randgen;
    cout << second_randgen.sample_gaussian(0, 1) << endl;


    return 0;
}

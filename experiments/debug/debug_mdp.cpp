#include <iostream>
#include <random>
#include <vector>
#include "space.h"
#include "random.h"
#include "vector_op.h"

int sample_from_prob(std::vector<double> prob, 
                     std::uniform_real_distribution<double>& distribution,
                     std::mt19937& generator)
{
    int n = prob.size();
    std::vector<double> cumul(n);
    cumul[0] = prob[0];
    for(int i = 1; i < n; i++)
    {
        cumul[i] = cumul[i-1] + prob[i];
        // std::cout << cumul[i] << std::endl;
    }
    double u = distribution(generator);
    // std::cout << "u = " << u << std::endl;
    int sample = 0;
    for(int i = 0; i < n; i++)
    {
        if (u <= cumul[i])
        {
            return i;
        }
    }
}

int main(void)
{

    /*
        Debug random
    */
    utils::Random randgen(42); 
    // std::vector<double> prob = {0.1, 0.5, 0.3, 0.05, 0.05};

    // int N = 1000000;
    // int P = 5;
    // std::vector<double> hist(P);

    // for(int i = 0; i < N; i++)
    // {
    //     int sample = randgen.choice(prob); 
    //     hist[sample] += 1.0/N;
    //     // std::cout << sample_from_prob(prob, distribution_unif, generator) << " ";
    // }
    // // std::cout << std::endl;

    // for(int i = 0; i < P; i++)
    // {
    //     std::cout << hist[i] << " ";
    // }
    // std::cout << std::endl;

    int N = 2;
    std::vector<double> samples(N);
    for(int i = 0; i < N; i++)
    {
        samples[i] = randgen.sample_gaussian(100, 2.0);
    }
    utils::printvec(samples);
    std::cout << "mean = " << utils::mean(samples) << std::endl;
    std::cout << "std = " << utils::stdev(samples) << std::endl;


    // // random seed
    // unsigned seed = 42;
    // std::mt19937 generator;
    // generator.seed(seed);

    // std::uniform_int_distribution<int> distribution(0,6);

    // // for(int i = 0; i < 10; i++)
    // // {
    // //     std::cout << distribution(generator) << ' ';
    // // }
    // // std::cout << std::endl;


    // // generating random sample from probability vector
    // int P = 5;
    // std::vector<double> prob = {0.1, 0.4, 0.4, 0.05, 0.05};
    // std::uniform_real_distribution<double> distribution_unif;
    // std::uniform_int_distribution<double> distribution_unif_int;
    // std::cout << distribution_unif_int.a() << " ///// " << distribution_unif_int.b() << std::endl;

    // int N = 1000000;
    // std::vector<double> hist(P);

    // for(int i = 0; i < N; i++)
    // {
    //     int sample = sample_from_prob(prob, distribution_unif, generator); 
    //     hist[sample] += 1.0/N;
    //     // std::cout << sample_from_prob(prob, distribution_unif, generator) << " ";
    // }
    // // std::cout << std::endl;

    // for(int i = 0; i < P; i++)
    // {
    //     std::cout << hist[i] << " ";
    // }
    // std::cout << std::endl;


    // std::cout<<"I'm here \n";


    /*
        Debug discrete spaces
    */ 

    // spaces::Discrete space(10);
    // std::vector<double> hist(10);
    // for(int k = 0; k < 100000; k++)
    // {
    //     int sample = space.sample();
    //     hist[sample] += 1.0/100000;
    //     std::cout << sample << " ";
    // }
    // std::cout << std::endl;

    // for(int i = 0; i < 10; i++)
    // {
    //     std::cout << hist[i] << " ";
    // }
    // std::cout << std::endl;


    /*
        Debug box spaces
    */
    // std::vector<double> low = {-1, -2, -3, -4, -5};
    // std::vector<double> high = {1, 10, 20, 30, 100};

    // std::vector<double> valid = {0, 5, 17, 20, 99};
    // std::vector<double> not_valid = {-1, 5, 30, 20, 101};

    // spaces::Box space(low, high, 12);

    // for(int k = 0; k < 10; k++)
    // {
    //     std::vector<double> sample = space.sample();
    //     std::cout << sample[0] << " ";
    //     std::cout << sample[1] << " ";
    //     std::cout << sample[2] << " ";
    //     std::cout << sample[3] << " ";
    //     std::cout << sample[4] << " ";
    //     std::cout << std::endl;
    // }
    // std::cout << std::endl;

    return 0;

}
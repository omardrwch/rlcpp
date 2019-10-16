#include <stdlib.h>
#include <random>
#include <assert.h> 
#include "space.h"


namespace spaces
{
    /*
    Members of Discrete
    */ 
    Discrete::Discrete(int num)
    {
        n = num;
    }

    Discrete::Discrete(int num, unsigned _seed)
    {
        n = num;
        generator.seed(_seed);
    }

    bool Discrete::contains(int x)
    {
        return (x >= 0 && x < n);
    }

    int Discrete::sample()
    {
        std::uniform_int_distribution<int> distribution(0,n-1);
        return distribution(generator);
    }


    /*
    Members of Box
    */
    Box::Box(std::vector<double> box_low, std::vector<double> box_high)
    {
        low = box_low;
        high = box_high;
        size = box_low.size();
        generator.seed(default_seed);
        assert(size == box_high.size() && "The size of box_low and box_high must be the same.");
    }    

    Box::Box(std::vector<double> box_low, std::vector<double> box_high, unsigned _seed)
    {
        low = box_low;
        high = box_high;
        size = box_low.size();
        generator.seed(_seed);
        assert(size == box_high.size() && "The size of box_low and box_high must be the same.");
    }    

    bool Box::contains(std::vector<double> x)
    {
        bool contains = true;
        if (x.size() != size)
        {
            contains = false;
        }
        for(int i = 0; i < x.size(); i++)
        {
            contains = contains && (x[i] >= low[i] && x[i] <= high[i]);
        }
        return contains;
    }

    std::vector<double> Box::sample()
    {
        // uniform real distribution
        std::uniform_real_distribution<double> distribution(0.0,1.0);

        std::vector<double> sampled_state(size);
        for(int i = 0; i < size; i++)
        {
           double a;
           double b;
           a = low[i];
           b = high[i];
           sampled_state[i] = a + (b-a)*distribution(generator);
        } 
        return sampled_state;
    }
}
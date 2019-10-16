#include <iostream>
#include <random>
#include <vector>
#include "space.h"
#include "utils.h"


int main(void)
{
    utils::vec_2d mat; 
    int n = 5;
    int m = 5;
    for(int i = 0; i < n; i++)
    {
        mat.push_back(std::vector<double>());
        for(int j = 0; j < m; j++)
        {
            mat[i].push_back(15.0);
        }
    }       

    utils::vec_2d lala; 
    lala = mat; 

    for(int i = 0; i < n; i++)
    {
        utils::printvec(lala[i]);
    }

    return 0;

}
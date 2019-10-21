/*

    There is nothing important in this file. I use this just to test a few things :)

*/

#include <iostream>
#include <random>
#include <vector>
#include "space.h"
#include "utils.h"


int main(void)
{
    utils::vec::vec_2d mat; 
    int n = 4;
    int m = 5;
    for(int i = 0; i < n; i++)
    {
        mat.push_back(std::vector<double>());
        for(int j = 0; j < m; j++)
        {
            mat[i].push_back(15.0);
        }
    }       

    utils::vec::vec_2d lala; 
    lala = mat; 

    for(int i = 0; i < n; i++)
    {
            utils::vec::printvec(lala[i]);
    }

    std::cout << lala.size() << std::endl;
    std::cout << lala[0].size() << std::endl;


    return 0;

}

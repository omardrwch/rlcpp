#include <vector>
#include <math.h>
#include <assert.h> 
#include <iostream>
#include "vector_op.h"


namespace utils
{
    double mean(std::vector<double> vec)
    {
        double result = 0;
        int n = vec.size();
        if (n == 0) {std::cerr << "Warning: calling mean() on empty vector." <<std::endl;}
        for(int i = 0; i < n; i++)
        {
            result += vec[i];
        }
        return result/((double) n);
    }

    double stdev(std::vector<double> vec)
    {
        int n = vec.size();
        if (n == 0) {std::cerr << "Warning: calling stdev() on empty vector." <<std::endl;}
        double mu = mean(vec);
        std::vector<double> aux(n);
        for(int i = 0; i < n; i++)
        {
            aux[i] = std::pow(vec[i]-mu, 2.0);
        }       
        return std::sqrt(mean(aux));
    }

    double inner_prod(std::vector<double> vec1, std::vector<double> vec2)
    {
        int n = vec1.size();
        assert( n == vec2.size() && "vec1 and vec2 must have the same size.");
        if (n == 0) {std::cerr << "Warning: calling inner_prod() on empty vectors." <<std::endl;}
        double result = 0.0;
        for(int i = 0; i < n; i++)
        {
            result += vec1[i]*vec2[i];
        }
        return result;
    }

    void printvec(std::vector<double> vec)
    {
        int n = vec.size();
        std::cout << "{";
        for(int i = 0; i < n; i++)
        {
            std::cout << vec[i];
            if (i < n-1){ std::cout << ", ";}
        }   
        std::cout << "}" << std::endl;
    }

    vec_2d get_zeros_2d(int dim1, int dim2, int dim3)
    {
        utils::vec_2d vector;
        for(int ii = 0; ii < dim1; ii++)
        {   
            vector.push_back(std::vector<double>());
            for(int jj = 0; jj < dim2; jj++) vector[ii].push_back(0.0);
        }   
        return vector;
    }

    vec_3d get_zeros_3d(int dim1, int dim2, int dim3)
    {
        utils::vec_3d vector;
        for(int ii = 0; ii < dim1; ii++)
        {   
            vector.push_back(std::vector<std::vector<double>>());
            for(int jj = 0; jj < dim2; jj++)
            {
                vector[ii].push_back(std::vector<double>());
                for(int kk = 0; kk < dim3; kk++) vector[ii][jj].push_back(0.0);
            }
        }   
        return vector;
    }
}
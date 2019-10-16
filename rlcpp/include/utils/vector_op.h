#ifndef __VECTOR_OP__
#define __VECTOR_OP__

/**
 * @file
 * @brief Common vector operations.
 */
namespace utils
{
    /**
     * @brief Computes the mean of a vector.
     */
    double mean(std::vector<double> vec); 

    /**
     * @brief Computes the standard deviation of a vector.
     */
    double stdev(std::vector<double> vec);

    /**
     * @brief Computes the inner product between vec1 and vec2
     * @param vec1
     * @param vec2
     * @return inner product
     */
    double inner_prod(std::vector<double> vec1, std::vector<double> vec2);

    /**
     * @brief Print vector
     */
    void printvec(std::vector<double> vec);
}

#endif
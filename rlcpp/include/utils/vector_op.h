#ifndef __VECTOR_OP__
#define __VECTOR_OP__

/**
 * @file
 * @brief Common vector operations.
 */

#include <vector>

namespace utils
{
    /**
     * Utils for common vector operations.
     */
    namespace vec
    {
        /**
         * @brief Type for 2d vector
         */
        typedef std::vector<std::vector<double>> vec_2d;

        /**
         * @brief Type for 3d vector
         */
        typedef std::vector<std::vector<std::vector<double>>> vec_3d;

        /**
         * @brief Computes the mean of a vector.
         * @param vec
         * @return mean of vec
         */
        double mean(std::vector<double> vec); 

        /**
         * @brief Computes the standard deviation of a vector.
         * @param vec
         * @return standard deviation of vec
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
         * @param vec
         */
        void printvec(std::vector<double> vec);

        /**
         * @brief Get 2d vector of doubles of dimensions (dim1, dim2) filled with zeros
         * @param dim1
         * @param dim2
         * @return vec_2d with dimensions (dim1, dim2)
         */
        vec_2d get_zeros_2d(int dim1, int dim2);

        /**
         * @brief Get 3d vector of doubles of dimensions (dim1, dim2, dim3) filled with zeros
         * @param dim1
         * @param dim2
         * @param dim3
         * @return vec_3d with dimensions (dim1, dim2, dim3)
         */
        vec_3d get_zeros_3d(int dim1, int dim2, int dim3);
    }
}

#endif
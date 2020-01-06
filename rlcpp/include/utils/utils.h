#ifndef __UTILS_H__
#define __UTILS_H__

#include "vector_op.h"
#include "random.h"
#include "noise.h"

/**
 * @file 
 * All utils headers.
 */


/**
 * @brief Useful definitions (random number generation, vector operations etc.)
 */
namespace utils
{

    // this should be defined in C++17
    /**
     * @brief Clamp a value between an upper and lower bound. Requires C++17.
     * @param v value to be clampled
     * @param lo lower bound
     * @param hi upper bound
     * @tparam T type of v, lo and hi
     */
    template<class T>
    constexpr const T& clamp( const T& v, const T& lo, const T& hi )
    {
        assert( !(hi < lo) );
        return (v < lo) ? lo : (hi < v) ? hi : v;
    }
}

#endif

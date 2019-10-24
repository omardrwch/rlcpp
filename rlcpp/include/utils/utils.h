#ifndef __UTILS_H__
#define __UTILS_H__

#include "vector_op.h"
#include "random.h"

/**
 * @file Gather all utils headers.
 */


/**
 * @brief Useful definitions (random number generation, vector operations etc.)
 */
namespace utils
{

// this should be defined in C++17
template<class T>
constexpr const T& clamp( const T& v, const T& lo, const T& hi )
{
    assert( !(hi < lo) );
    return (v < lo) ? lo : (hi < v) ? hi : v;
}
}

#endif

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "space.h"
#include <stdlib.h>
#include <array>



TEST_CASE( "Testing discrete spaces", "[discrete_space]" )
{
    // set seed
    srand(42);

    spaces::Discrete space(5);
    REQUIRE( space.n == 5 );
    REQUIRE( space.contains(0) );
    REQUIRE( space.contains(4) );
    REQUIRE( !space.contains(5) );

    bool ok = true;
    for(int i = 0; i<15; i++)
    {
        ok = ok && space.contains(space.sample());
    }
    REQUIRE( ok );
}

TEST_CASE( "Testing box spaces", "[box_space]")
{
    // set seed
    srand(42);

    const int SIZE = 5; 
    std::array<double, SIZE> low = {-1, -2, -3, -4, -5};
    std::array<double, SIZE> high = {1, 10, 20, 30, 100};

    std::array<double, SIZE> valid = {0, 5, 17, 20, 99};
    std::array<double, SIZE> not_valid = {-1, 5, 30, 20, 101};

    spaces::Box<SIZE> space(low, high);

    REQUIRE( space.contains(valid) );
    REQUIRE( !space.contains(not_valid) );

    bool ok = true;
    for(int i = 0; i<25; i++)
    {
        ok = ok && space.contains(space.sample());
    }
    REQUIRE( ok );
}
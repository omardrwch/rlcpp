#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "space.h"
#include <stdlib.h>
#include <vector>


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

    std::vector<double> low = {-1, -2, -3, -4, -5};
    std::vector<double> high = {1, 10, 20, 30, 100};

    std::vector<double> valid = {0, 5, 17, 20, 99};
    std::vector<double> not_valid = {-1, 5, 30, 20, 101};

    spaces::Box space(low, high);

    REQUIRE( space.contains(valid) );
    REQUIRE( !space.contains(not_valid) );

    bool space_contains_sample = true;
    for(int i = 0; i<25; i++)
    {
        space_contains_sample = space_contains_sample && space.contains(space.sample());
    }
    
    REQUIRE( space_contains_sample );
}
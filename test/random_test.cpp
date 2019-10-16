#include <vector>
#include "catch.hpp"
#include "random.h"

TEST_CASE( "Testing Random::choice", "[choice]" )
{
    utils::Random randgen(42); 
    std::vector<double> prob = {0.1, 0.2, 0.3, 0.4};
    std::vector<double> prob2 = {1.0, 0.0, 0.0, 0.0};
    std::vector<double> prob3 = {0.0, 1.0, 0.0, 0.0};
    std::vector<double> prob4 = {0.0, 0.0, 1.0, 0.0};
    std::vector<double> prob5 = {0.0, 0.0, 0.0, 1.0};

    REQUIRE( randgen.choice(prob, 0)    == 0 );
    REQUIRE( randgen.choice(prob, 0.05) == 0 );
    REQUIRE( randgen.choice(prob, 0.10001) == 1 );
    REQUIRE( randgen.choice(prob, 0.15) == 1 );
    REQUIRE( randgen.choice(prob, 0.30001) == 2 );
    REQUIRE( randgen.choice(prob, 0.59999) == 2 );
    REQUIRE( randgen.choice(prob, 0.60001) == 3 );
    REQUIRE( randgen.choice(prob, 0.8) == 3 );
    REQUIRE( randgen.choice(prob, 1.0) == 3 );

    REQUIRE( randgen.choice(prob2) == 0 );
    REQUIRE( randgen.choice(prob3) == 1 );
    REQUIRE( randgen.choice(prob4) == 2 );
    REQUIRE( randgen.choice(prob5) == 3 );
}
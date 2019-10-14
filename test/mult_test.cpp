#include "catch.hpp"
#include "mult.h"

TEST_CASE( "Multiplication is ok", "[mult]" ) {
    REQUIRE( mult(1, 2) == 2 );
    REQUIRE( mult(2, 3) == 6 );
}


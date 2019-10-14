#define CATCH_CONFIG_MAIN // Define this in ONLY ONE file. This tells catch.hpp to generate a main() function
#include "catch.hpp"
#include "sum.h"

TEST_CASE( "Sum is ok", "[sum]" ) {
    REQUIRE( sum(1, 2) == 3 );
    REQUIRE( sum(2, 3) == 5 );
}

// int main(void)
// {
//     int x = 1;
//     int y = 2;
//     assert(sum(x, y) == 3);
// }
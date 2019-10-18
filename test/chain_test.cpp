#include "catch.hpp"
#include "chain.h"
#include "mdp.h"

TEST_CASE( "Testing chain", "[chain]" )
{
    mdp::Chain chain(3);
    REQUIRE( chain.id.compare("Chain") == 0);  
    REQUIRE( chain.state == 0);

    mdp::StepResult<int> step_result; 
    
    step_result = chain.step(0);
    REQUIRE( (chain.state == 1 && step_result.reward == 0) );

    step_result = chain.step(1); 
    REQUIRE( (chain.state == 0 && step_result.reward == 0) );

    step_result = chain.step(0);
    step_result = chain.step(0);
    REQUIRE( (chain.state == 2 && step_result.reward == 1.0) );
}
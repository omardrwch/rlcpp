/*
    To run this example:
    $ bash scripts/compile.sh vi_example && ./build/examples/vi_example
*/

#include <iostream>
#include <vector>
#include <string>
#include "mdp.h"
#include "episodicvi.h"
#include "utils.h"

using namespace std;
using namespace utils::vec;

int main(void)
{
    /*   Defining a simple MDP with 3 states and 2 actions  */

    mdp::Chain mdp(20);
    cout << mdp.id << endl << endl;

    int horizon = 21;

    mdp::EpisodicVI vi(mdp, horizon);
    vi.run();

    cout << "Value function" << endl;
    for (int h=0; h<=horizon; h++)
    {
      printvec(vi.V[h]);
    }

    cout << "Policy" << endl;
    for (int h=0; h<horizon; h++)
    {
      printvec(vi.greedy_policy[h]);
    }

    return 0;
}

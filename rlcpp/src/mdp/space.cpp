#include <stdlib.h>
#include "space.h"

namespace spaces
{
    /*
    Members of Discrete
    */ 
    Discrete::Discrete(int num)
    {
        n = num;
    }

    bool Discrete::contains(int x)
    {
        return (x >= 0 && x < n);
    }

    int Discrete::sample()
    {
        return rand() % n;
    }

}
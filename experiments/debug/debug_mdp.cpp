#include <iostream>
#include <array>
#include "space.h"

// void foo(std::array<double, 5>& array)
// {
//     std::array<double, 5> local_array = array;
//     local_array[0] = -5;
//     // std::array<double, 5>* local_array;
//     // local_array = &array;
//     // (*local_array)[0] = -5;
// }

int main(void)
{

    /*
      Testing discrete spaces
    */
    // spaces::Discrete space(5);
    // std::cout << "Samples: \n";
    // for(int k=0; k < 20; k++){ std::cout << space.sample() << "\n";}
    // std::cout << "\n";
    // std::cout << space.n << "----" << space.contains(0) << " " << space.contains(4) << " "  <<space.contains(5) << "\n" ;


    // std::array<double, 5> array = {10, 20, 30, 40};
    // foo(array);
    // std::cout << array[0] << std::endl; 
    // return 0;


    // /*
    //   Testing box spaces
    // */

    // const int SIZE = 5; 
    // std::array<double, SIZE> low = {-1, -2, -3, -4, -5};
    // std::array<double, SIZE> high = {1, 10, 20, 30, 100};
    // std::array<double, SIZE> test = {-1, 5, 17, 20, 101};

    // spaces::Box<SIZE> box(low, high);
    
    // for(int k = 0; k < box.low.size(); k++){std::cout<<box.low[k]<< " ";}
    // std::cout << std::endl;

    // for(int k = 0; k < box.high.size(); k++){std::cout<<box.high[k]<< " ";}
    // std::cout << std::endl;

    // std::cout<<"Size = "<<box.size<< "\n" ;

    // std::cout<<"Contains test = "<<box.contains(test)<< "\n" ;

    std::cout<<"I'm here \n";

    return 0;

}
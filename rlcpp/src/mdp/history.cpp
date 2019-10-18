#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "history.h"

/*
    Following this answer: https://stackoverflow.com/a/13952386/5691288
*/

namespace mdp
{
    /*
        -----------------------------------------------------------------------------------------------------
        Initialization of History for types <int, int> and related implementations (e.g., used in FiniteMDP).
        -----------------------------------------------------------------------------------------------------
    */ 
    template class History<int, int>;

    /**
     * @brief Print first N entries of the history.
     * @param N
     */
    template <>
    void History<int, int>::print(unsigned int N)
    {
        int n = std::min(N, length);
        std::cout << std::endl << " -------------- First " << n << " entries of history --------------" << std::endl;
        for(int i = 0; i < n; i ++)
        {
            std::cout << " | "  << "state = "       << states[i] ;
            std::cout << " | "  << "action = "      << actions[i] ;
            std::cout << " | "  << "next state = "  << next_states[i];
            std::cout << " | "  << "reward = "      << rewards[i];
            for(int j = 0; j < n_extra_variables; j++)
            {
                std::cout << " | "  << extra_variables[j].name <<" = "   << extra_variables[j].data[i];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }


    /**
     * @brief Write history in csv file
     * @param filename example: "myfile.csv"
     */
    template <>
    void History<int, int>::to_csv(std::string filename)
    {
        std::ofstream file;
        file.open (filename);
        file << "state,action,next_state, reward,";
        for(int j = 0; j < n_extra_variables; j++) file << extra_variables[j].name << ",";
        file << "\n";
        for(int i = 0; i < length; i ++)
        {
            file << states[i] << ",";
            file << actions[i] << ",";
            file << next_states[i] << ",";
            file << rewards[i] << ",";
            for(int j = 0; j < n_extra_variables; j++)
            {
                file <<  extra_variables[j].data[i] << ",";
            }
            file << "\n";
        }      
        file.close();
    }


    /*
        -----------------------------------------------------------------------------------------------------
        Initialization of History for types <std::vector<double>, int> and related implementations (e.g., might be used in
        enviroments with box states and discrete actions)
        -----------------------------------------------------------------------------------------------------
    */ 
   template class History<std::vector<double>, int>;
}
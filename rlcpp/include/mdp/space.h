#ifndef __SPACE_H__
#define __SPACE_H__

#include <vector>
#include <random>

/**
 * @file
 * @brief Classes for definining observation and action spaces.
 */

namespace spaces
{

    /**
     * @brief Possible space names.
     */
    enum spc_name {undefined, discrete, box}; 

    /**
     * @brief Base class for observation and action spaces.
     * 
     */
    template <typename T> 
    class Space
    {
    public:
        Space(/* args */){};
        ~Space(){};
        /**
         * @brief Sample a value of the space with a uniform distribution
         */
        virtual T sample()=0;

        /**
         * @brief Returns true if x belongs to the space, and false otherwise.
         * @param x 
         */
        virtual bool contains(T x)=0;

        /**
         * Name of the space (discrete, box, etc.)
         */
        spc_name name = undefined; 

        /**
         * Random number generator
         */
        std::mt19937 generator;
    };


    /**
     * @brief Class for discrete spaces.
     * Set of possible values = {0, ..., n-1}
     */
    class Discrete: public Space<int>
    {
    public:
        /**
         * @param num: Value of n
         */
        Discrete(int num);

        /**
         * @param num: Value of n
         * @param _seed: seed for random number generation
         */
        Discrete(int num, unsigned _seed);
        ~Discrete(){};

        /**
         * Number of elements in the space.
         */
        int n; 

        int sample();
        bool contains(int x);

        spc_name name = discrete;
    };


    /**
     * @brief Class for box spaces in R^n
     */
    class Box: public Space<std::vector<double>>
    {
    public:
        /**
         * @param box_low: array contaning the lower bounds of the box
         * @param box_high: array containing the upper bounds of the box
         */
        Box(std::vector<double>box_low, std::vector<double> box_high);

        /**
         * @param box_low: array contaning the lower bounds of the box
         * @param box_high: array containing the upper bounds of the box
         * @param _seed: seed for random number generation
         */
        Box(std::vector<double>box_low, std::vector<double> box_high, unsigned _seed);
        ~Box(){};

        // Methods of base class
        std::vector<double> sample();
        bool contains(std::vector<double> x);
        spc_name name = box;

        // Attributes

        /**
         * Size of the fox
         */
        int size; 

        /**
         * lower bounds of the box
         */
        std::vector<double> low;

        /**
         * upper bounds of the box
         */
        std::vector<double> high;

        /**
         * Default seed
         */
        unsigned default_seed = 42;
    };
}
#endif
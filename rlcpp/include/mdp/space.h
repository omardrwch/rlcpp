#ifndef __SPACE_H__
#define __SPACE_H__

#include <vector>
#include <random>

/**
 * @file
 * @brief Classes for definining observation and action spaces.
 */

/**
 * @brief Definitions for observation and action spaces.
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
        virtual T sample() {T foo; return foo;};

        /**
         * @brief Returns true if x belongs to the space, and false otherwise.
         * @param x 
         */
        virtual bool contains(T x) {return false;};

        /**
         * Name of the space (discrete, box, etc.)
         */
        spc_name name = undefined; 

        /**
         * Random number generator
         */
        std::mt19937 generator;

        /**
         * Size of the space (-1 for infinity or undefined )
         */
        int n = -1;
    };


    /**
     * @brief Class for discrete spaces.
     * Set of possible values = {0, ..., n-1}
     */
    class Discrete: public Space<int>
    {
    public:

        /**
         * @brief Default constructor
         */
        Discrete();

        /**
         * @param _n: Value of n
         * @param _seed: seed for random number generation (default = 42)
         */
        Discrete(int _n, unsigned _seed = 42);
        ~Discrete(){};

        /**
         * Number of elements in the space.
         */
        int n; 

        // Methods

        /**
         * @brief Set the value of n, that defines the discrete space {0, ..., n-1}
         */
        void set_n(int _n);

        // Methods of base class
        int sample();
        bool contains(int x);

        /**
         * Name of the space
         */
        spc_name name = discrete;
    };


    /**
     * @brief Class for box spaces in R^n
     */
    class Box: public Space<std::vector<double>>
    {
    public:

        /**
         * @brief Default constructor
         */
        Box();

        /**
         * @param _low: array contaning the lower bounds of the box
         * @param _high: array containing the upper bounds of the box
         * @param _seed: seed for random number generation (default = 42)
         */
        Box(std::vector<double> _low, std::vector<double> _high, unsigned _seed = 42);
        ~Box(){};

        // Methods
        /**
         * @brief Define the lower and upper bounds of the box
         * @param _low: array contaning the lower bounds of the box
         * @param _high: array containing the upper bounds of the box
         */ 
        void set_bounds(std::vector<double> _low, std::vector<double> _high);

        // Methods of base class
        std::vector<double> sample();
        bool contains(std::vector<double> x);

        /**
         * Name of the space
         */
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
    };
}
#endif
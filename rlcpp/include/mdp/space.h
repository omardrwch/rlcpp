#ifndef __SPACE_H__
#define __SPACE_H__

#include <vector>
#include <assert.h> 

/**
 * @file
 * @brief Classes for definining observation and action spaces.
 */

namespace spaces
{
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
        ~Discrete(){};

        /**
         * Number of elements in the space.
         */
        int n; 

        int sample();
        bool contains(int x);
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
        ~Box(){};

        // Methods of base class
        std::vector<double> sample();
        bool contains(std::vector<double> x);

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
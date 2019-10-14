#ifndef __SPACE_H__
#define __SPACE_H__

#include <array>


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
    template<int SIZE>
    class Box: public Space<std::array<double, SIZE>>
    {
    public:
        /**
         * @param box_low: array contaning the lower bounds of the box
         * @param box_high: array containing the upper bounds of the box
         */
        Box(std::array<double, SIZE> box_low, std::array<double, SIZE> box_high);
        ~Box(){};

        // Methods of base class
        std::array<double, SIZE> sample();
        bool contains(std::array<double, SIZE> x);

        // Attributes

        /**
         * Size of the fox
         */
        int size = SIZE; 

        /**
         * lower bounds of the box
         */
        std::array<double, SIZE> low;

        /**
         * upper bounds of the box
         */
        std::array<double, SIZE> high;
    };

    /*
    Members of Box
    */

    template<int SIZE>
    Box<SIZE>::Box(std::array<double, SIZE> box_low, std::array<double, SIZE> box_high)
    {
        low = box_low;
        high = box_high;
    }    

    template<int SIZE>
    bool Box<SIZE>::contains(std::array<double, SIZE> x)
    {
        bool contains = true;
        for(int i = 0; i < x.size(); i++)
        {
            contains = contains && (x[i] >= low[i] && x[i] <= high[i]);
        }
        return contains;
    }

    template<int SIZE>
    std::array<double, SIZE> Box<SIZE>::sample()
    {
        std::array<double, SIZE> temp; 
        return temp;
    }
}
#endif
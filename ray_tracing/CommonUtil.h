#ifndef COMMONUTIL_H
#define COMMONUTIL_H

#include <random>


/**
 * return random number in [0,1)
 */
inline double GetRandomDouble()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;

    return distribution(generator);
}

/**
 * return random number in [min,max)
 */
inline double GetRandomDouble(double min, double max)
{
    return min + (max - min) * GetRandomDouble();
}


#endif //COMMONUTIL_H

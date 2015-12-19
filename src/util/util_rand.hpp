// Copyright (c) 2015 Matthew MacGregor
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef _UTIL_RAND_HPP_
#define _UTIL_RAND_HPP_

#include <random>
#include <ctime>
#include <type_traits>

// float GenerateRandom(float min, float max);
// int GenerateRandom(int min, int max); 

template<typename Num>
Num GenerateRandomInt(Num min, Num max) 
{
    static std::mt19937 rng_engine((unsigned)time(nullptr));
    static std::uniform_int_distribution<Num> distribution(min, max);
    return distribution(rng_engine);
}

template<typename Num>
Num GenerateRandomFloat(Num min, Num max) 
{
    static std::mt19937 rng_engine((unsigned)time(nullptr));
    static std::uniform_real_distribution<Num> distribution(min, max);
    return distribution(rng_engine);
}


#endif

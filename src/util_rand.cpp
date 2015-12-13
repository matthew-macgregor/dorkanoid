#include "util_rand.hpp"

float _floatrand(float min, float max) {
    static std::mt19937 rng_engine( (unsigned)time(nullptr) );
    static std::uniform_real_distribution<float> distribution(min, max);
    return distribution(rng_engine);
}

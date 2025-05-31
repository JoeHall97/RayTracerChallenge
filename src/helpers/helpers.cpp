#include "helpers.h"
#include <cmath>

static constexpr float EPSILON = 0.000001;

bool areFloatsEqual(const float a, const float b)
{
    return std::abs(a - b) <= EPSILON;
}

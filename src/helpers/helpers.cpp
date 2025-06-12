#include "helpers.hpp"

#include <cmath>

static constexpr float EPSILON = 0.00001;

bool rtc::areFloatsEqual(const float a, const float b) {
  return std::abs(a - b) <= EPSILON;
}

#pragma once
#include <cstdlib>

namespace rtc {
constexpr float EPSILON = 0.001;

inline bool areFloatsEqual(const float a, const float b) {
  return std::abs(a - b) <= EPSILON;
}
} // namespace rtc

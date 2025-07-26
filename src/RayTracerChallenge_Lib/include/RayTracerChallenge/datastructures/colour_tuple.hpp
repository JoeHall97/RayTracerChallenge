#pragma once

#include <RayTracerChallenge/helpers/helpers.hpp>
#include <ostream>

namespace rtc {
struct ColourTuple {
  float red, green, blue;

  ColourTuple() = default;

  ColourTuple(const float red, const float green, const float blue)
      : red{red}, green{green}, blue{blue} {}

  bool operator==(const ColourTuple &rhs) const noexcept {
    return areFloatsEqual(red, rhs.red) && areFloatsEqual(green, rhs.green) &&
           areFloatsEqual(blue, rhs.blue);
  }

  ColourTuple operator+(const ColourTuple &rhs) const noexcept {
    return ColourTuple{red + rhs.red, green + rhs.green, blue + rhs.blue};
  }

  ColourTuple operator-(const ColourTuple &rhs) const noexcept {
    return ColourTuple{red - rhs.red, green - rhs.green, blue - rhs.blue};
  }

  ColourTuple operator*(const float &value) const noexcept {
    return ColourTuple{red * value, green * value, blue * value};
  }

  ColourTuple operator*(const ColourTuple &rhs) const noexcept {
    return ColourTuple{red * rhs.red, green * rhs.green, blue * rhs.blue};
  }
};
} // namespace rtc

std::ostream &operator<<(std::ostream &os, const rtc::ColourTuple &t);

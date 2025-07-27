#pragma once

#include <RayTracerChallenge/helpers/helpers.hpp>
#include <ostream>

namespace rtc {
struct Colour {
  float red, green, blue;

  Colour() = default;

  Colour(const float red, const float green, const float blue)
      : red{red}, green{green}, blue{blue} {}

  bool operator==(const Colour &rhs) const noexcept {
    return areFloatsEqual(red, rhs.red) && areFloatsEqual(green, rhs.green) &&
           areFloatsEqual(blue, rhs.blue);
  }

  Colour operator+(const Colour &rhs) const noexcept {
    return Colour{red + rhs.red, green + rhs.green, blue + rhs.blue};
  }

  Colour operator-(const Colour &rhs) const noexcept {
    return Colour{red - rhs.red, green - rhs.green, blue - rhs.blue};
  }

  Colour operator*(const float &value) const noexcept {
    return Colour{red * value, green * value, blue * value};
  }

  Colour operator*(const Colour &rhs) const noexcept {
    return Colour{red * rhs.red, green * rhs.green, blue * rhs.blue};
  }
};
} // namespace rtc

std::ostream &operator<<(std::ostream &os, const rtc::Colour &t);

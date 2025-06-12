#include "colour_tuple.hpp"

#include <ostream>

#include "helpers.hpp"

using rtc::ColourTuple;

bool ColourTuple::operator==(const ColourTuple &rhs) const {
  return rtc::areFloatsEqual(red, rhs.red) && rtc::areFloatsEqual(green, rhs.green) &&
         rtc::areFloatsEqual(blue, rhs.blue);
}

ColourTuple ColourTuple::operator+(const ColourTuple &rhs) const {
  return ColourTuple{red + rhs.red, green + rhs.green, blue + rhs.blue};
}

ColourTuple ColourTuple::operator-(const ColourTuple &rhs) const {
  return ColourTuple{red - rhs.red, green - rhs.green, blue - rhs.blue};
}

ColourTuple ColourTuple::operator*(const float &value) const {
  return ColourTuple{red * value, green * value, blue * value};
}

ColourTuple ColourTuple::operator*(const ColourTuple &rhs) const {
  return ColourTuple{red * rhs.red, green * rhs.green, blue * rhs.blue};
}

std::ostream &operator<<(std::ostream &os, const ColourTuple &t) {
  os << '{' << t.red << ", " << t.green << ", " << t.blue << '}';
  return os;
}

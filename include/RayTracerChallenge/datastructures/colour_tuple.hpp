#pragma once
#include <ostream>

namespace rtc {
class ColourTuple {
 public:
  float red, green, blue;

  ColourTuple(float red, float green, float blue)
      : red{red}, green{green}, blue{blue} {}

  bool operator==(const ColourTuple& rhs) const;
  ColourTuple operator+(const ColourTuple& rhs) const;
  ColourTuple operator-(const ColourTuple& rhs) const;
  ColourTuple operator*(const float& value) const;
  ColourTuple operator*(const ColourTuple& rhs) const;
};
}

std::ostream& operator<<(std::ostream& os, const rtc::ColourTuple& t);

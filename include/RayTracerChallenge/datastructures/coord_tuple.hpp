#pragma once

#include <ostream>

namespace rtc {
struct CoordTuple {
 public:
  float x, y, z, w;

  CoordTuple(const float x, const float y, const float z, const float w)
      : x{x}, y{y}, z{z}, w{w} {}
  CoordTuple() = default;

  bool operator==(const CoordTuple& rhs) const;
  CoordTuple operator+(const CoordTuple& rhs) const;
  CoordTuple operator-(const CoordTuple& rhs) const;
  CoordTuple operator-() const;
  CoordTuple operator*(float value) const;
  CoordTuple operator/(float value) const;

  [[nodiscard]] inline bool isVector() const { return w == 0; }
  [[nodiscard]] inline bool isPoint() const { return w == 1; }

  [[nodiscard]] float magnitude() const;
  [[nodiscard]] CoordTuple normalise() const;
  [[nodiscard]] float dot(const CoordTuple& b) const;
  [[nodiscard]] CoordTuple cross(const CoordTuple& b) const;
};

inline CoordTuple point(const float x, const float y, const float z) {
  return CoordTuple{x, y, z, 1};
}
inline CoordTuple vector(const float x, const float y, const float z) {
  return CoordTuple{x, y, z, 0};
}
}  // namespace rtc

std::ostream& operator<<(std::ostream& os, const rtc::CoordTuple& t);

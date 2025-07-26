#pragma once

#include <RayTracerChallenge/helpers/helpers.hpp>
#include <ostream>

namespace rtc {
struct CoordTuple {
public:
  float x, y, z, w;

  CoordTuple(const float x, const float y, const float z, const float w)
      : x{x}, y{y}, z{z}, w{w} {}
  CoordTuple() = default;

  bool operator==(const CoordTuple &rhs) const noexcept {
    return w == rhs.w && areFloatsEqual(x, rhs.x) && areFloatsEqual(y, rhs.y) &&
           areFloatsEqual(z, rhs.z);
  }

  CoordTuple operator+(const CoordTuple &rhs) const noexcept {
    return CoordTuple{x + rhs.x, y + rhs.y, z + rhs.z, std::max(w, rhs.w)};
  }

  CoordTuple operator-(const CoordTuple &rhs) const noexcept {
    return CoordTuple{x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w};
  }

  CoordTuple operator-() const noexcept { return CoordTuple{-x, -y, -z, -w}; }

  CoordTuple operator*(const float value) const noexcept {
    return CoordTuple{x * value, y * value, z * value, w * value};
  }

  CoordTuple operator/(const float value) const noexcept {
    return CoordTuple{x / value, y / value, z / value, w / value};
  }

  [[nodiscard]] bool isVector() const noexcept { return w == 0.0f; }

  [[nodiscard]] bool isPoint() const noexcept { return w == 1.0f; }

  [[nodiscard]] float magnitude() const noexcept {
    return static_cast<float>(std::sqrt(std::pow(x, 2) + std::pow(y, 2) +
                                        std::pow(z, 2) + std::pow(w, 2)));
  }

  [[nodiscard]] CoordTuple normalise() const noexcept {
    const auto mag = magnitude();
    return CoordTuple{x / mag, y / mag, z / mag, w / mag};
  }

  [[nodiscard]] float dot(const CoordTuple &b) const noexcept {
    return x * b.x + y * b.y + z * b.z + w * b.w;
  }

  [[nodiscard]] CoordTuple cross(const CoordTuple &b) const noexcept {
    return CoordTuple{y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x,
                      w};
  }

  [[nodiscard]] CoordTuple reflect(const CoordTuple &normal) const noexcept {
    return *this - normal * 2.0f * dot(normal);
  }
};

inline CoordTuple point(const float x, const float y, const float z) noexcept {
  return CoordTuple{x, y, z, 1};
}
inline CoordTuple vector(const float x, const float y, const float z) noexcept {
  return CoordTuple{x, y, z, 0};
}
} // namespace rtc

std::ostream &operator<<(std::ostream &os, const rtc::CoordTuple &t);

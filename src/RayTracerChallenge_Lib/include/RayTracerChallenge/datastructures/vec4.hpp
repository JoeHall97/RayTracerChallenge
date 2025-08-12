#pragma once

#include <RayTracerChallenge/helpers/helpers.hpp>
#include <cmath>
#include <ostream>

namespace rtc {
struct Vec4 {
  float x, y, z, w;

  Vec4(const float x, const float y, const float z, const float w)
      : x{x}, y{y}, z{z}, w{w} {}
  Vec4() = default;

  bool operator==(const Vec4 &rhs) const noexcept {
    return w == rhs.w && areFloatsEqual(x, rhs.x) && areFloatsEqual(y, rhs.y) &&
           areFloatsEqual(z, rhs.z);
  }

  Vec4 operator+(const Vec4 &rhs) const noexcept {
    return Vec4{x + rhs.x, y + rhs.y, z + rhs.z, std::max(w, rhs.w)};
  }

  Vec4 operator-(const Vec4 &rhs) const noexcept {
    return Vec4{x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w};
  }

  Vec4 operator-() const noexcept { return Vec4{-x, -y, -z, -w}; }

  Vec4 operator*(const float value) const noexcept {
    return Vec4{x * value, y * value, z * value, w * value};
  }

  Vec4 operator/(const float value) const noexcept {
    return Vec4{x / value, y / value, z / value, w / value};
  }

  [[nodiscard]] bool isVector() const noexcept { return w == 0.0f; }

  [[nodiscard]] bool isPoint() const noexcept { return w == 1.0f; }

  [[nodiscard]] float magnitude() const noexcept {
    return static_cast<float>(std::sqrt(std::pow(x, 2) + std::pow(y, 2) +
                                        std::pow(z, 2) + std::pow(w, 2)));
  }

  [[nodiscard]] Vec4 normalise() const noexcept {
    const auto mag = magnitude();
    return Vec4{x / mag, y / mag, z / mag, w / mag};
  }

  [[nodiscard]] float dot(const Vec4 &b) const noexcept {
    return x * b.x + y * b.y + z * b.z + w * b.w;
  }

  [[nodiscard]] Vec4 cross(const Vec4 &b) const noexcept {
    return Vec4{y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x, w};
  }

  [[nodiscard]] Vec4 reflect(const Vec4 &normal) const noexcept {
    return *this - normal * 2.0f * dot(normal);
  }
};

inline Vec4 point(const float x, const float y, const float z) noexcept {
  return Vec4{x, y, z, 1};
}
inline Vec4 vector(const float x, const float y, const float z) noexcept {
  return Vec4{x, y, z, 0};
}
} // namespace rtc

std::ostream &operator<<(std::ostream &os, const rtc::Vec4 &t);

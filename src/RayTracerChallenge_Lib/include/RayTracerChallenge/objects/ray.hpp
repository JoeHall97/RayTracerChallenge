#pragma once

#include <RayTracerChallenge/datastructures/matrix.hpp>
#include <RayTracerChallenge/datastructures/vec4.hpp>

namespace rtc {
struct Ray {
public:
  Vec4 origin;
  Vec4 direction;

  Ray(const Vec4 origin, const Vec4 direction)
      : origin{origin}, direction{direction} {}

  [[nodiscard]]
  inline Vec4 position(const float time) const {
    return origin + direction * time;
  }

  [[nodiscard]]
  Ray transform(const Matrix &m) const;
};
} // namespace rtc

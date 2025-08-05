#pragma once

#include <RayTracerChallenge/datastructures/vec4.hpp>
#include <RayTracerChallenge/objects/colour.hpp>

namespace rtc {
struct Light {
  Colour intensity;
  Vec4 position;

  Light() = default;
  Light(const Colour &intensity, const Vec4 &position)
      : intensity(intensity), position(position) {}
};
} // namespace rtc
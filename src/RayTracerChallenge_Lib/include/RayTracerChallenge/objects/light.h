#pragma once

#include <RayTracerChallenge/datastructures/colour_tuple.hpp>
#include <RayTracerChallenge/datastructures/coord_tuple.hpp>

namespace rtc {
struct Light {
  ColourTuple intensity;
  CoordTuple position;

  Light(const ColourTuple &intensity, const CoordTuple &position)
      : intensity(intensity), position(position) {}
};
} // namespace rtc
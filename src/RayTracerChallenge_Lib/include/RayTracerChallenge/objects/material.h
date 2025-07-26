#pragma once

#include <RayTracerChallenge/datastructures/colour_tuple.hpp>
#include <RayTracerChallenge/helpers/helpers.hpp>
#include <RayTracerChallenge/objects/light.h>

namespace rtc {
struct Material {
  ColourTuple colour;
  float ambient, diffuse, specular, shininess;

  Material(const ColourTuple colour, const float ambient, const float diffuse,
           const float specular, const float shininess)
      : colour(colour), ambient(ambient), diffuse(diffuse), specular(specular),
        shininess(shininess) {}

  bool operator==(const Material &rhs) const noexcept {
    return colour == rhs.colour && areFloatsEqual(ambient, rhs.ambient) &&
           areFloatsEqual(diffuse, rhs.diffuse) &&
           areFloatsEqual(specular, rhs.specular) &&
           areFloatsEqual(shininess, rhs.shininess);
  }

  [[nodiscard]]
  ColourTuple lighting(const Light &light, const CoordTuple &position,
                       const CoordTuple &eyeVec,
                       const CoordTuple &normalVec) const noexcept;
};

[[nodiscard]] inline Material defaultMaterial() noexcept {
  const ColourTuple defaultColour{1, 1, 1};
  return Material{defaultColour, 0.1, 0.9, 0.9, 200.0};
}

} // namespace rtc
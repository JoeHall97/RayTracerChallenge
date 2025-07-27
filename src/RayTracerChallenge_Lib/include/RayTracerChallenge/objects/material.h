#pragma once

#include <RayTracerChallenge/helpers/helpers.hpp>
#include <RayTracerChallenge/objects/colour.hpp>
#include <RayTracerChallenge/objects/light.hpp>

namespace rtc {
struct Material {
  Colour colour;
  float ambient, diffuse, specular, shininess;

  Material(const Colour colour, const float ambient, const float diffuse,
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
  Colour lighting(const Light &light, const Vec4 &position, const Vec4 &eyeVec,
                  const Vec4 &normalVec) const noexcept;
};

[[nodiscard]] inline Material defaultMaterial() noexcept {
  const Colour defaultColour{1, 1, 1};
  return Material{defaultColour, 0.1, 0.9, 0.9, 200.0};
}

} // namespace rtc
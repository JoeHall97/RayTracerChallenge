#pragma once

#include <RayTracerChallenge/helpers/helpers.hpp>
#include <RayTracerChallenge/objects/colour.hpp>
#include <RayTracerChallenge/objects/light.hpp>
#include <RayTracerChallenge/objects/patterns.hpp>
#include <memory>

namespace rtc {

struct Material {
  Colour colour;
  std::unique_ptr<Pattern> pattern;
  float ambient, diffuse, specular, shininess, reflective, transparency,
      refractiveIndex;

  Material(const Colour colour, const float ambient, const float diffuse,
           const float specular, const float shininess, const float reflective,
           const float transparency, const float refractiveIndex)
      : colour(colour), pattern(nullptr), ambient(ambient), diffuse(diffuse),
        specular(specular), shininess(shininess), reflective(reflective),
        transparency(transparency), refractiveIndex(refractiveIndex) {}

  Material(const Colour colour, std::unique_ptr<Pattern> pattern,
           const float ambient, const float diffuse, const float specular,
           const float shininess, const float reflective,
           const float transparency, const float refractiveIndex)
      : colour(colour), pattern(std::move(pattern)), ambient(ambient),
        diffuse(diffuse), specular(specular), shininess(shininess),
        reflective(reflective), transparency(transparency),
        refractiveIndex(refractiveIndex) {}

  Material(const Material &other)
      : colour(other.colour),
        pattern(other.pattern ? other.pattern->clone() : nullptr),
        ambient(other.ambient), diffuse(other.diffuse),
        specular(other.specular), shininess(other.shininess),
        reflective(other.reflective), transparency(other.transparency),
        refractiveIndex(other.refractiveIndex) {}

  Material(Material &&other) noexcept
      : colour(other.colour),
        pattern(other.pattern ? std::move(other.pattern) : nullptr),
        ambient(other.ambient), diffuse(other.diffuse),
        specular(other.specular), shininess(other.shininess),
        reflective(other.reflective), transparency(other.transparency),
        refractiveIndex(other.refractiveIndex) {}

  Material &operator=(const Material &rhs) noexcept {
    if (this == &rhs) {
      return *this;
    }

    colour = rhs.colour;
    pattern = rhs.pattern ? rhs.pattern->clone() : nullptr;
    ambient = rhs.ambient;
    diffuse = rhs.diffuse;
    specular = rhs.specular;
    shininess = rhs.shininess;
    reflective = rhs.reflective;
    transparency = rhs.transparency;
    refractiveIndex = rhs.refractiveIndex;
    return *this;
  }

  Material &operator=(Material &&rhs) noexcept {
    if (this == &rhs) {
      return *this;
    }

    colour = rhs.colour;
    pattern = rhs.pattern ? std::move(rhs.pattern) : nullptr;
    ambient = rhs.ambient;
    diffuse = rhs.diffuse;
    specular = rhs.specular;
    shininess = rhs.shininess;
    reflective = rhs.reflective;
    transparency = rhs.transparency;
    refractiveIndex = rhs.refractiveIndex;
    return *this;
  }

  bool operator==(const Material &rhs) const noexcept {
    return colour == rhs.colour && areFloatsEqual(ambient, rhs.ambient) &&
           areFloatsEqual(diffuse, rhs.diffuse) &&
           areFloatsEqual(specular, rhs.specular) &&
           areFloatsEqual(shininess, rhs.shininess) &&
           areFloatsEqual(reflective, rhs.reflective) &&
           areFloatsEqual(transparency, rhs.transparency) &&
           areFloatsEqual(refractiveIndex, rhs.refractiveIndex);
  }

  [[nodiscard]]
  Colour lighting(const Object *object, const Light &light,
                  const Vec4 &position, const Vec4 &eyeVec,
                  const Vec4 &normalVec, bool inShadow = false) const noexcept;
};

[[nodiscard]] inline Material defaultMaterial() noexcept {
  return Material{Colour{1, 1, 1}, 0.1, 0.9, 0.9, 200.0, 0.0, 0.0, 1.0f};
}
} // namespace rtc

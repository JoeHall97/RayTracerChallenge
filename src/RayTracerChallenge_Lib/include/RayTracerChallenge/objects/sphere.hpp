#pragma once

#include <RayTracerChallenge/datastructures/matrix.hpp>
#include <RayTracerChallenge/datastructures/vec4.hpp>
#include <RayTracerChallenge/helpers/helpers.hpp>
#include <RayTracerChallenge/objects/intersection.hpp>
#include <RayTracerChallenge/objects/material.h>
#include <RayTracerChallenge/objects/object.hpp>
#include <RayTracerChallenge/objects/ray.hpp>

namespace rtc {
struct Sphere final : Object {
  Matrix transform;
  Material material;
  Vec4 origin;
  float radius;

  Sphere(const Vec4 origin, const float radius)
      : transform{identity(4)}, material{defaultMaterial()}, origin{origin},
        radius{radius} {}

  Sphere(const Vec4 origin, const float radius, const Matrix &transform)
      : transform{transform}, material{defaultMaterial()}, origin{origin},
        radius{radius} {}

  bool operator==(const Sphere &rhs) const noexcept {
    return origin == rhs.origin && areFloatsEqual(radius, rhs.radius);
  }
  bool operator==(const Object &rhs) const noexcept override {
    if (const auto s = dynamic_cast<const Sphere *>(&rhs); s != nullptr)
      return origin == s->origin && areFloatsEqual(radius, s->radius);
    return false;
  }

  bool operator!=(const Sphere &rhs) const noexcept { return !(*this == rhs); }

  [[nodiscard]]
  SortedIntersections intersect(const Ray &ray) const noexcept;
  [[nodiscard]]
  Vec4 normalAt(const Vec4 &worldPoint) const noexcept;
};

[[nodiscard]] inline Sphere sphere() noexcept {
  return Sphere{point(0, 0, 0), 1};
}

} // namespace rtc

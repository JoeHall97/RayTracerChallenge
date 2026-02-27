#pragma once

#include <RayTracerChallenge/datastructures/matrix.hpp>
#include <RayTracerChallenge/datastructures/vec4.hpp>
#include <RayTracerChallenge/helpers/helpers.hpp>
#include <RayTracerChallenge/objects/intersection.hpp>
#include <RayTracerChallenge/objects/material.hpp>
#include <RayTracerChallenge/objects/object.hpp>
#include <RayTracerChallenge/objects/ray.hpp>

namespace rtc {
struct Sphere final : Object {
  Vec4 origin;
  float radius;

  Sphere(const Vec4 origin, const float radius)
      : origin{origin}, radius{radius}, material{defaultMaterial()},
        transform{identity(4)} {}

  Sphere(const Vec4 &origin, const float radius, const Material &material)
      : origin{origin}, radius{radius}, material{material},
        transform{identity(4)} {}

  Sphere(const Vec4 origin, const float radius, const Matrix &transform)
      : origin{origin}, radius{radius}, material{defaultMaterial()},
        transform{transform} {}

  bool operator==(const Sphere &rhs) const noexcept {
    return origin == rhs.origin && areFloatsEqual(radius, rhs.radius);
  }
  bool operator==(const Object &rhs) const noexcept override {
    if (const auto s = dynamic_cast<const Sphere *>(&rhs); s != nullptr) {
      return origin == s->origin && areFloatsEqual(radius, s->radius);
    }
    return false;
  }
  std::ostream &operator<<(std::ostream &os) const override;

  bool operator!=(const Sphere &rhs) const noexcept { return !(*this == rhs); }

  [[nodiscard]]
  SortedIntersections
  localIntersect(const Ray &localRay) const noexcept override;
  [[nodiscard]]
  Vec4 localNormalAt(const Vec4 &localPoint) const noexcept override {
    return localPoint - point(0, 0, 0);
  }

  [[nodiscard]] Material getMaterial() const noexcept override {
    return material;
  }
  void setMaterial(const Material &m) noexcept override { material = m; }

  [[nodiscard]] Matrix getTransformationMatrix() const noexcept override {
    return transform;
  }
  void setTransformationMatrix(const Matrix &m) noexcept override {
    transform = m;
  }

private:
  Material material;
  Matrix transform;
};

[[nodiscard]] inline Sphere sphere() noexcept {
  return Sphere{point(0, 0, 0), 1};
}

} // namespace rtc

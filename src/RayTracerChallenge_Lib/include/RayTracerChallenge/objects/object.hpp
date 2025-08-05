#pragma once

#include "intersection.hpp"
#include "material.hpp"

#include <RayTracerChallenge/objects/ray.hpp>

namespace rtc {
struct Object {
  Material material;
  virtual ~Object() = default;
  Object() : material{defaultMaterial()} {}
  explicit Object(Material const &material) : material(material) {}
  virtual bool operator==(const Object &other) const = 0;
  virtual std::ostream &operator<<(std::ostream &os) const = 0;
  virtual Vec4 normalAt(const Vec4 &worldPoint) const noexcept = 0;
};
} // namespace rtc

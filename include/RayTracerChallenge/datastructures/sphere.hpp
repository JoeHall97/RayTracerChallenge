#pragma once

#include "coord_tuple.hpp"
#include "helpers.hpp"
#include "object.hpp"

namespace rtc {
struct Sphere final : Object {
 public:
  CoordTuple origin;
  float radius;

  Sphere(const CoordTuple origin, const float radius)
      : origin{origin}, radius{radius} {}

  ~Sphere() override = default;

  inline bool operator==(const Sphere &rhs) const {
    return origin == rhs.origin && areFloatsEqual(radius, rhs.radius);
  }
  bool operator==(const Object &rhs) const override {
    if ( const auto s = dynamic_cast<const Sphere*>(&rhs); s != nullptr)
      return origin == s->origin && areFloatsEqual(radius, s->radius);
    return false;
  }

  inline bool operator!=(const Sphere &rhs) const { return !(*this == rhs); }
};
inline Sphere sphere() { return Sphere{point(0, 0, 0), 1}; }
}  // namespace rtc

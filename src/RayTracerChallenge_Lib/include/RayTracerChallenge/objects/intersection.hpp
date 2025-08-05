#pragma once

#include <RayTracerChallenge/helpers/helpers.hpp>
#include <RayTracerChallenge/objects/object.hpp>
#include <optional>
#include <ostream>
#include <set>

namespace rtc {
struct Intersection {
  float t;
  const Object *object;

  Intersection(const float t, const Object *o) : t{t}, object{o} {}

  bool operator==(const Intersection &other) const noexcept {
    return areFloatsEqual(t, other.t) && object == other.object;
  }
};

struct IntersectionCompare {
  bool operator()(const Intersection &lhs, const Intersection &rhs) const {
    return lhs.t < rhs.t;
  }
};

// a sorted set of Intersections by t ascending
using SortedIntersections = std::set<Intersection, IntersectionCompare>;
SortedIntersections intersections(const std::vector<Object *> &objects,
                                  const Ray &ray);

std::optional<Intersection> hit(const SortedIntersections &intersections);
} // namespace rtc

std::ostream &operator<<(std::ostream &os, const rtc::Intersection &i);

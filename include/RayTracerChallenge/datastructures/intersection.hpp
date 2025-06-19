#pragma once

#include <ostream>
#include <set>

#include "object.hpp"

namespace rtc {
struct Intersection {
  const float t;
  const Object &object;

  Intersection(const float t, const Object &o) : t{t}, object{o} {}

  bool operator==(const Intersection &other) const noexcept {
    return t == other.t && object == other.object;
  }
};

struct IntersectionCompare {
  inline bool operator()(const Intersection &lhs, const Intersection &rhs) const {
    return lhs.t < rhs.t;
  }
}; 

// sorted set of Intersections by t ascending
using SortedIntersections = std::set<Intersection, IntersectionCompare>;

std::optional<Intersection> hit(const SortedIntersections &intersections);
}  // namespace rtc

std::ostream &operator<<(std::ostream &os, const rtc::Intersection &t);

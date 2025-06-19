#include "intersection.hpp"

#include <optional>
#include <ostream>

#include "sphere.hpp"

using rtc::Intersection;

std::optional<Intersection> rtc::hit(
    const rtc::SortedIntersections &intersections) {
  for (auto i : intersections) {
    if (i.t < 0) continue;
    return i;
  }
  return std::optional<Intersection>{};
}

std::ostream &operator<<(std::ostream &os, const rtc::Intersection &i) {
  os << '{' << i.t;
  try {
    const auto &s = dynamic_cast<const rtc::Sphere &>(i.object);
    os << ", rtc::Sphere}";
  } catch (std::bad_cast ex) {
    os << ", rtc::Object}";
  }
  return os;
}

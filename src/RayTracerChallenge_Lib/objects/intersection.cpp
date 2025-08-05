#include <RayTracerChallenge/objects/intersection.hpp>
#include <RayTracerChallenge/objects/sphere.hpp>
#include <optional>
#include <ostream>

using rtc::Intersection;

std::optional<Intersection> rtc::hit(const SortedIntersections &intersections) {
  for (auto i : intersections) {
    if (i.t < 0)
      continue;
    return i;
  }
  return std::optional<Intersection>{};
}

std::ostream &operator<<(std::ostream &os, const Intersection &i) {
  os << '{' << i.t;
  if (const auto s = dynamic_cast<const rtc::Sphere *>(i.object);
      s != nullptr) {
    os << ", rtc::Sphere, " << s->transform << "}";
  }
  return os;
}

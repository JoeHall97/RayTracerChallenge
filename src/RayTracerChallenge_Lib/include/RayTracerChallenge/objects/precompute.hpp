#pragma once

#include <RayTracerChallenge/objects/intersection.hpp>
#include <RayTracerChallenge/objects/object.hpp>
#include <RayTracerChallenge/objects/ray.hpp>

namespace rtc {
struct Precompute {
  Vec4 point, eyeVec, normalVec, overPoint, reflectVec;
  const Object *object;
  float t, n1, n2;
  bool inside;
};

Precompute prepareComputation(const Intersection &intersection, const Ray &ray);
Precompute prepareComputation(const Intersection &intersection, const Ray &ray,
                              const SortedIntersections &intersections);
} // namespace rtc

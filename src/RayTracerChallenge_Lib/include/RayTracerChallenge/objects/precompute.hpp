#pragma once

#include <RayTracerChallenge/objects/intersection.hpp>
#include <RayTracerChallenge/objects/object.hpp>
#include <RayTracerChallenge/objects/ray.hpp>

namespace rtc {
struct Precompute {
  Vec4 point, eyeVec, normalVec;
  const Object *object;
  float t;
  bool inside;
};

Precompute prepareComputation(const Intersection &intersection, const Ray &ray);
} // namespace rtc
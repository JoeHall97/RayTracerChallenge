#pragma once

#include <RayTracerChallenge/objects/intersection.hpp>
#include <RayTracerChallenge/objects/light.hpp>
#include <RayTracerChallenge/objects/object.hpp>
#include <RayTracerChallenge/objects/precompute.hpp>
#include <vector>

namespace rtc {
struct World {
  std::vector<std::unique_ptr<Object>> objects;
  Light light;

  [[nodiscard]] SortedIntersections intersections(const Ray &ray) const;
  [[nodiscard]] Colour shadeHit(const Precompute &comp) const noexcept {
    return comp.object->material.lighting(light, comp.point, comp.eyeVec,
                                          comp.normalVec);
  }
  [[nodiscard]] Colour colourAt(const Ray &ray) const noexcept;
};

World defaultWorld() noexcept;
} // namespace rtc
#pragma once

#include <RayTracerChallenge/objects/intersection.hpp>
#include <RayTracerChallenge/objects/light.hpp>
#include <RayTracerChallenge/objects/object.hpp>
#include <RayTracerChallenge/objects/precompute.hpp>
#include <memory>
#include <vector>

namespace rtc {
struct World {
  std::vector<std::unique_ptr<Object>> objects;
  Light light;

  [[nodiscard]] SortedIntersections intersections(const Ray &ray) const;

  [[nodiscard]] Colour shadeHit(const Precompute &comp) const noexcept {
    const auto shadowed = isShadowed(comp.overPoint);
    return comp.object->material.lighting(light, comp.overPoint, comp.eyeVec,
                                          comp.normalVec, shadowed);
  }

  [[nodiscard]] Colour colourAt(const Ray &ray) const noexcept;
  [[nodiscard]] bool isShadowed(const Vec4 &point) const noexcept;
};

World defaultWorld() noexcept;
} // namespace rtc

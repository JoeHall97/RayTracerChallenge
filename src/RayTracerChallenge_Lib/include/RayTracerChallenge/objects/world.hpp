#pragma once

#include <RayTracerChallenge/objects/intersection.hpp>
#include <RayTracerChallenge/objects/light.hpp>
#include <RayTracerChallenge/objects/object.hpp>
#include <RayTracerChallenge/objects/precompute.hpp>
#include <cstdint>
#include <memory>
#include <vector>

namespace rtc {
struct World {
  std::vector<std::unique_ptr<Object>> objects;
  Light light;

  [[nodiscard]] SortedIntersections intersections(const Ray &ray) const;
  [[nodiscard]] Colour shadeHit(const Precompute &comp,
                                const uint8_t depth) const noexcept;
  [[nodiscard]] Colour reflectedColour(const Precompute &comp,
                                       const uint8_t depth) const noexcept;
  [[nodiscard]] Colour refractedColour(const Precompute &comp,
                                       const uint8_t depth) const noexcept;
  [[nodiscard]] Colour colourAt(const Ray &ray,
                                const uint8_t depth) const noexcept;
  [[nodiscard]] bool isShadowed(const Vec4 &point) const noexcept;
};

World defaultWorld() noexcept;
} // namespace rtc

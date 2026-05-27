#include "RayTracerChallenge/objects/colour.hpp"
#include "RayTracerChallenge/objects/patterns.hpp"
#include "RayTracerChallenge/objects/precompute.hpp"
#include <RayTracerChallenge/objects/sphere.hpp>
#include <RayTracerChallenge/objects/world.hpp>
#include <cmath>
#include <cstdint>

rtc::World rtc::defaultWorld() noexcept {
  World w{};
  w.light = Light{Colour{1, 1, 1}, point(-10, 10, -10)};
  auto s1 = sphere();
  auto s1Material = s1.getMaterial();
  s1Material.colour = Colour{0.8f, 1.0f, 0.6f};
  s1Material.diffuse = 0.7f;
  s1.setMaterial(s1Material);
  w.objects.push_back(std::make_unique<Sphere>(s1));
  auto s2 = sphere();
  s2.setTransformationMatrix(scalingMatrix(0.5f, 0.5f, 0.5f));
  w.objects.push_back(std::make_unique<Sphere>(s2));
  return w;
}

rtc::SortedIntersections rtc::World::intersections(const Ray &ray) const {
  SortedIntersections intersections{};
  for (const auto &o : objects) {
    if (const auto i = o->intersect(ray); !i.empty()) {
      intersections.insert(i.begin(), i.end());
    }
  }
  return intersections;
}

rtc::Colour rtc::World::colourAt(const Ray &ray,
                                 const uint8_t depth) const noexcept {
  const auto xs = intersections(ray);
  const auto hit = rtc::hit(xs);
  if (!hit.has_value()) {
    return Colour{0, 0, 0};
  }
  const auto comp = prepareComputation(hit.value(), ray, xs);
  return shadeHit(comp, depth);
}

bool rtc::World::isShadowed(const Vec4 &point) const noexcept {
  const auto v = light.position - point;
  const auto distance = v.magnitude();
  const auto direction = v.normalise();

  const auto r = Ray{point, direction};
  const auto xs = intersections(r);

  const auto hit = rtc::hit(xs);
  return hit.has_value() && hit.value().t < distance;
}

[[nodiscard]] rtc::Colour
rtc::World::reflectedColour(const Precompute &comp,
                            const uint8_t depth) const noexcept {
  if (comp.object->getMaterial().reflective == 0 || depth == 0) {
    return BLACK;
  }

  const auto reflectRay = Ray{comp.overPoint, comp.reflectVec};
  const auto colour = colourAt(reflectRay, depth - 1);

  return colour * comp.object->getMaterial().reflective;
}

[[nodiscard]] rtc::Colour
rtc::World::shadeHit(const Precompute &comp,
                     const uint8_t depth) const noexcept {
  const auto shadowed = isShadowed(comp.overPoint);
  const auto material = comp.object->getMaterial();
  const auto surface = material.lighting(comp.object, light, comp.overPoint,
                                         comp.eyeVec, comp.normalVec, shadowed);

  const auto reflected = reflectedColour(comp, depth);
  const auto refracted = refractedColour(comp, depth);

  if (material.transparency > 0 && material.reflective > 0) {
    const auto reflectance = comp.schlick();
    return surface + reflected * reflectance + refracted * (1 - reflectance);
  }

  return surface + reflected + refracted;
}

[[nodiscard]] rtc::Colour
rtc::World::refractedColour(const Precompute &comp,
                            const uint8_t depth) const noexcept {
  const auto material = comp.object->getMaterial();
  if (material.transparency == 0 || depth == 0) {
    return rtc::BLACK;
  }

  // find the ratio of first index of refraction to the second
  const auto nRatio = comp.n1 / comp.n2;
  // cos(theta_i) is the same as the dot product of the two vectors
  const auto cosi = comp.eyeVec.dot(comp.normalVec);
  // find sin(theta_t)^2 via trig. identity
  const auto sin2t = (nRatio * nRatio) * (1 - cosi * cosi);

  if (sin2t > 1) {
    return rtc::BLACK;
  }

  // find cos(theta_t) via trig. identity
  const auto cost = std::sqrt(1.0f - sin2t);
  // compute the direction of the refracted ray
  const auto direction =
      comp.normalVec * (nRatio * cosi - cost) - comp.eyeVec * nRatio;
  // create the refracted ray
  const rtc::Ray refactedRay{comp.underPoint, direction};

  // find the colour of the refracted ray
  return colourAt(refactedRay, depth - 1) * material.transparency;
}

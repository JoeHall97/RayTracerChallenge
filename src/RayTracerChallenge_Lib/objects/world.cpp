#include <RayTracerChallenge/objects/sphere.hpp>
#include <RayTracerChallenge/objects/world.hpp>

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

rtc::Colour rtc::World::colourAt(const Ray &ray) const noexcept {
  const auto xs = intersections(ray);
  const auto hit = rtc::hit(xs);
  if (!hit.has_value())
    return Colour{0, 0, 0};
  const auto comp = prepareComputation(hit.value(), ray);
  return shadeHit(comp);
}

rtc::Colour
rtc::World::colourAtWithReflections(const Ray &ray,
                                    const uint8_t depth) const noexcept {
  const auto xs = intersections(ray);
  const auto hit = rtc::hit(xs);
  if (!hit.has_value()) {
    return Colour{0, 0, 0};
  }
  const auto comp = prepareComputation(hit.value(), ray);
  return shadeHitWithReflections(comp, depth);
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
  const auto colour = colourAtWithReflections(reflectRay, depth - 1);

  return colour * comp.object->getMaterial().reflective;
}

[[nodiscard]] rtc::Colour
rtc::World::shadeHit(const Precompute &comp) const noexcept {
  const auto shadowed = isShadowed(comp.overPoint);
  return comp.object->getMaterial().lighting(comp.object, light, comp.overPoint,
                                             comp.eyeVec, comp.normalVec,
                                             shadowed);
}

[[nodiscard]] rtc::Colour
rtc::World::shadeHitWithReflections(const Precompute &comp,
                                    const uint8_t depth) const noexcept {
  const auto shadowed = isShadowed(comp.overPoint);
  const auto surface = comp.object->getMaterial().lighting(
      comp.object, light, comp.overPoint, comp.eyeVec, comp.normalVec,
      shadowed);
  const auto reflected = reflectedColour(comp, depth);
  return surface + reflected;
}

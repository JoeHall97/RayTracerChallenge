#include <RayTracerChallenge/objects/sphere.hpp>
#include <RayTracerChallenge/objects/world.hpp>

rtc::World rtc::defaultWorld() noexcept {
  World w{};
  w.light = Light{Colour{1, 1, 1}, point(-10, 10, -10)};
  auto s1 = sphere();
  s1.material.colour = Colour{0.8f, 1.0f, 0.6f};
  s1.material.diffuse = 0.7f;
  w.objects.push_back(std::make_unique<Sphere>(s1));
  auto s2 = sphere();
  s2.transform = scalingMatrix(0.5f, 0.5f, 0.5f);
  w.objects.push_back(std::make_unique<Sphere>(s2));
  return w;
}

rtc::SortedIntersections rtc::World::intersections(const Ray &ray) const {
  SortedIntersections xs{};
  for (const auto &o : objects) {
    if (const auto s = dynamic_cast<const Sphere *>(o.get()); s != nullptr) {
      const auto i = s->intersect(ray);
      xs.insert(i.begin(), i.end());
    }
  }
  return xs;
}

rtc::Colour rtc::World::colourAt(const Ray &ray) const noexcept {
  const auto xs = intersections(ray);
  const auto hit = rtc::hit(xs);
  if (!hit.has_value())
    return Colour{0, 0, 0};
  const auto comp = prepareComputation(hit.value(), ray);
  return shadeHit(comp);
}

#include <RayTracerChallenge/objects/intersection.hpp>
#include <RayTracerChallenge/objects/sphere.hpp>

rtc::SortedIntersections
rtc::Sphere::localIntersect(const Ray &localRay) const noexcept {
  // the vector from the sphere's center, to the Ray's origin
  const auto sphereToRay = localRay.origin - point(0, 0, 0);
  const auto a = localRay.direction.dot(localRay.direction);
  const auto b = 2 * localRay.direction.dot(sphereToRay);
  const auto c = sphereToRay.dot(sphereToRay) - 1;

  const auto discriminant = (b * b) - 4 * a * c;
  if (discriminant < 0)
    return SortedIntersections{};

  const Intersection i1{(-b - std::sqrt(discriminant)) / (2 * a), this};
  const Intersection i2{(-b + std::sqrt(discriminant)) / (2 * a), this};
  return SortedIntersections{i1, i2};
}

std::ostream &rtc::Sphere::operator<<(std::ostream &os) const {
  os << "Sphere";
  return os;
}

#include <RayTracerChallenge/objects/intersection.hpp>
#include <RayTracerChallenge/objects/sphere.hpp>

rtc::SortedIntersections rtc::Sphere::intersect(const Ray &ray) const noexcept {
  // the vector from the sphere's center, to the Ray's origin
  const auto transformedRay = ray.transform(transform.inverse());
  const auto sphereToRay = transformedRay.origin - origin;
  const auto a = transformedRay.direction.dot(transformedRay.direction);
  const auto b = 2 * transformedRay.direction.dot(sphereToRay);
  const auto c = sphereToRay.dot(sphereToRay) - 1;

  const auto discriminant = (b * b) - 4 * a * c;
  if (discriminant < 0)
    return SortedIntersections{};

  const Intersection i1{(-b - std::sqrt(discriminant)) / (2 * a), this};
  const Intersection i2{(-b + std::sqrt(discriminant)) / (2 * a), this};
  return SortedIntersections{i1, i2};
}

rtc::Vec4 rtc::Sphere::normalAt(const Vec4 &worldPoint) const noexcept {
  const auto objectPoint = transform.inverse() * worldPoint;
  const auto objectNormal = objectPoint - point(0, 0, 0);
  auto worldNormal = transform.inverse().transpose() * objectNormal;
  worldNormal.w = 0;
  return worldNormal.normalise();
}
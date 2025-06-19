#include "ray.hpp"

#include "intersection.hpp"
#include "sphere.hpp"

using rtc::Ray, rtc::Intersection;

std::vector<Intersection> Ray::intersect(Sphere &s) const
{
    // the vector from the sphere's center, to the ray's origin
    const auto sphereToRay = origin - s.origin;
    const auto a = direction.dot(direction);
    const auto b = 2 * direction.dot(sphereToRay);
    const auto c = sphereToRay.dot(sphereToRay) - 1;

    const auto discriminant = (b * b) - 4 * a * c;
    if (discriminant < 0)
        return std::vector<Intersection>{};

    const Intersection i1{(-b - std::sqrt(discriminant)) / (2 * a), s};
    const Intersection i2{(-b + std::sqrt(discriminant)) / (2 * a), s};
    return std::vector{i1, i2};
}

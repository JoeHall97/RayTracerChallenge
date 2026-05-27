#include <RayTracerChallenge/datastructures/matrix.hpp>
#include <RayTracerChallenge/objects/ray.hpp>

using rtc::Ray;

Ray Ray::transform(const Matrix &m) const {
  return Ray{m * origin, m * direction};
}

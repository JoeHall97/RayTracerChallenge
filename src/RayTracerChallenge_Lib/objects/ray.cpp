#include <RayTracerChallenge/datastructures/matrix.hpp>
#include <RayTracerChallenge/objects/ray.hpp>

using rtc::Ray;

// how do you determine what kind of matrix transformation to do?
Ray Ray::transform(const Matrix &m) const {
  return Ray{m * origin, m * direction};
}

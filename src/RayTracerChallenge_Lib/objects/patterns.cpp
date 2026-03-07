#include <RayTracerChallenge/objects/colour.hpp>
#include <RayTracerChallenge/objects/object.hpp>
#include <RayTracerChallenge/objects/patterns.hpp>

[[nodiscard]] rtc::Colour
rtc::StripePattern::colourAtObject(const Object *shape,
                                   const Vec4 &worldPoint) const noexcept {
  // we use the inverse of these matrices because they transform object->world,
  // but we need to go from world->object.
  const auto objectPoint =
      shape->getTransformationMatrix().inverse() * worldPoint;
  const auto patternPoint = getTransformationMatrix().inverse() * objectPoint;
  return colourAt(patternPoint);
}
#pragma once

#include <RayTracerChallenge/objects/intersection.hpp>
#include <RayTracerChallenge/objects/material.hpp>
#include <RayTracerChallenge/objects/ray.hpp>

namespace rtc {
struct Object {
  virtual ~Object() = default;

  virtual bool operator==(const Object &other) const = 0;
  virtual std::ostream &operator<<(std::ostream &os) const = 0;
  [[nodiscard]] virtual Vec4
  localNormalAt(const Vec4 &localPoint) const noexcept = 0;
  [[nodiscard]] virtual Material getMaterial() const noexcept = 0;
  virtual void setMaterial(const Material &m) noexcept = 0;
  [[nodiscard]] virtual Matrix getTransformationMatrix() const noexcept = 0;
  virtual void setTransformationMatrix(const Matrix &m) noexcept = 0;
  [[nodiscard]] virtual SortedIntersections
  localIntersect(const Ray &localRay) const noexcept = 0;

  [[nodiscard]] SortedIntersections intersect(const Ray &ray) const noexcept {
    const auto localRay = ray.transform(getTransformationMatrix().inverse());
    return localIntersect(localRay);
  }

  [[nodiscard]] Vec4 normalAt(const Vec4 &worldPoint) const noexcept {
    const auto localPoint = getTransformationMatrix().inverse() * worldPoint;
    const auto localNormal = localNormalAt(localPoint);
    auto worldNormal =
        getTransformationMatrix().inverse().transpose() * localNormal;
    worldNormal.w = 0;

    return worldNormal.normalise();
  }
};
} // namespace rtc

#pragma once

#include <RayTracerChallenge/objects/object.hpp>

namespace rtc {
class Plane : public Object {
public:
  Plane() : transform(rtc::identity(4)), material(defaultMaterial()) {}
  Plane(const Matrix &transform, const Material &material)
      : transform{transform}, material{material} {}

  bool operator==(const Object &other) const override {
    if (const auto p = dynamic_cast<const Plane *>(&other); p != nullptr) {
      return true;
    }
    return false;
  }

  std::ostream &operator<<(std::ostream &os) const override {
    os << "Plane";
    return os;
  }

  [[nodiscard]] Vec4
  localNormalAt(const Vec4 & /* localPoint */) const noexcept override {
    return vector(0, 1, 0);
  }

  [[nodiscard]] SortedIntersections
  localIntersect(const Ray &localRay) const noexcept override {
    if (std::abs(localRay.direction.y) < EPSILON) {
      return SortedIntersections{};
    }
    return SortedIntersections{
        Intersection{-localRay.origin.y / localRay.direction.y, this}};
  }

  [[nodiscard]] Material getMaterial() const noexcept override {
    return material;
  }
  void setMaterial(const Material &m) noexcept override { material = m; }
  [[nodiscard]] Matrix getTransformationMatrix() const noexcept override {
    return transform;
  }
  void setTransformationMatrix(const Matrix &m) noexcept override {
    transform = m;
  }

private:
  Matrix transform;
  Material material;
};

inline Plane plane() { return Plane{}; }
} // namespace rtc
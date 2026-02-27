#pragma once
#include <RayTracerChallenge/objects/object.hpp>

namespace rtc {
class TestShape : public Object {
public:
  TestShape(const Matrix &transform, const Material &material)
      : transform{transform}, material{material},
        savedRay{point(0, 0, 0), vector(0, 0, 0)} {}

  bool operator==(const Object &other) const override {
    if (const auto s = dynamic_cast<const TestShape *>(&other); s != nullptr)
      return true;
    return false;
  }

  std::ostream &operator<<(std::ostream &os) const override {
    os << "TestShape";
    return os;
  }

  [[nodiscard]] Vec4
  localNormalAt(const Vec4 &worldPoint) const noexcept override {
    return vector(worldPoint.x, worldPoint.y, worldPoint.z);
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
  [[nodiscard]] SortedIntersections
  localIntersect(const Ray &ray) const noexcept override {
    savedRay = ray;
    return SortedIntersections{};
  }

  [[nodiscard]] Ray getSavedRay() const noexcept { return savedRay; }

private:
  Matrix transform;
  Material material;
  mutable Ray savedRay;
};

[[nodiscard]] inline TestShape testShape() noexcept {
  return TestShape{identity(4), defaultMaterial()};
}
} // namespace rtc
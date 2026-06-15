#pragma once

#include <RayTracerChallenge/datastructures/matrix.hpp>
#include <RayTracerChallenge/datastructures/vec4.hpp>
#include <RayTracerChallenge/helpers/helpers.hpp>
#include <RayTracerChallenge/objects/intersection.hpp>
#include <RayTracerChallenge/objects/material.hpp>
#include <RayTracerChallenge/objects/object.hpp>
#include <limits>
#include <tuple>

namespace rtc {
struct Cube final : Object {
public:
  explicit Cube()
      : _transformation(rtc::identity(4)), _material(rtc::defaultMaterial()) {}
  explicit Cube(const Matrix &transform)
      : _transformation(transform), _material(rtc::defaultMaterial()) {}
  explicit Cube(const Material &material)
      : _transformation(rtc::identity(4)), _material(material) {}

  Cube(const Matrix &transform, const Material &material)
      : _transformation(transform), _material(material) {}

  bool operator==(const Object &other) const override { return this == &other; }

  std::ostream &operator<<(std::ostream &os) const override {
    os << "Cube";
    return os;
  }

  [[nodiscard("")]] Vec4
  localNormalAt(const Vec4 &localPoint) const noexcept override {
    const auto absX = std::abs(localPoint.x);
    const auto absY = std::abs(localPoint.y);
    const auto absZ = std::abs(localPoint.z);

    const auto maxC = std::max(absX, std::max(absY, absZ));

    if (areFloatsEqual(maxC, absX)) {
      return vector(localPoint.x, 0, 0);
    }
    if (areFloatsEqual(maxC, absY)) {
      return vector(0, localPoint.y, 0);
    }
    return vector(0, 0, localPoint.z);
  }

  [[nodiscard("")]] Material getMaterial() const noexcept override {
    return _material;
  }

  void setMaterial(const Material &m) noexcept override { _material = m; }

  [[nodiscard("")]] Matrix getTransformationMatrix() const noexcept override {
    return _transformation;
  }

  void setTransformationMatrix(const Matrix &m) noexcept override {
    _transformation = m;
  }

  [[nodiscard("")]] SortedIntersections
  localIntersect(const Ray &localRay) const noexcept override {
    const auto xMinAndMax = checkAxis(localRay.origin.x, localRay.direction.x);
    const auto yMinAndMax = checkAxis(localRay.origin.y, localRay.direction.y);
    const auto zMinAndMax = checkAxis(localRay.origin.z, localRay.direction.z);

    const auto tMin =
        std::max(std::get<0>(xMinAndMax),
                 std::max(std::get<0>(yMinAndMax), std::get<0>(zMinAndMax)));
    const auto tMax =
        std::min(std::get<1>(xMinAndMax),
                 std::min(std::get<1>(yMinAndMax), std::get<1>(zMinAndMax)));

    if (tMin > tMax) {
      return SortedIntersections{};
    }

    return SortedIntersections{Intersection{tMin, this},
                               Intersection{tMax, this}};
  }

private:
  Matrix _transformation;
  Material _material;

  [[nodiscard]]
  static std::tuple<float, float> checkAxis(const float origin,
                                            const float direction) noexcept {
    const auto tMinNumerator = -1 - origin;
    const auto tMaxNumerator = 1 - origin;

    float tMin, tMax;
    if (std::abs(direction) >= EPSILON) {
      tMin = tMinNumerator / direction;
      tMax = tMaxNumerator / direction;
    } else {
      tMin = tMinNumerator * std::numeric_limits<float>::max();
      tMax = tMaxNumerator * std::numeric_limits<float>::max();
    }

    if (tMin > tMax) {
      std::swap(tMin, tMax);
    }

    return std::tuple<float, float>{tMin, tMax};
  }
};
} // namespace rtc

#pragma once

#include <RayTracerChallenge/datastructures/matrix.hpp>
#include <RayTracerChallenge/datastructures/vec4.hpp>
#include <RayTracerChallenge/objects/colour.hpp>
#include <memory>

namespace rtc {
const auto BLACK = Colour{0, 0, 0};
const auto WHITE = Colour{1, 1, 1};

struct Object;

class Pattern {
public:
  virtual ~Pattern() = default;

  [[nodiscard]] virtual Colour colourAt(const Vec4 &point) const noexcept = 0;
  [[nodiscard]] virtual Colour
  colourAtObject(const Object *shape,
                 const Vec4 &worldPoint) const noexcept = 0;

  [[nodiscard]] virtual Matrix getTransformationMatrix() const noexcept = 0;
  virtual void setTransformationMatrix(const Matrix &matrix) noexcept = 0;
  [[nodiscard]] virtual std::unique_ptr<Pattern> clone() const noexcept = 0;
};

class StripePattern : public Pattern {
public:
  Colour a;
  Colour b;

  StripePattern(const Colour &a, const Colour &b)
      : a{a}, b{b}, transformationMatrix{identity(4)} {}
  StripePattern(const Colour &a, const Colour &b, const Matrix &matrix)
      : a{a}, b{b}, transformationMatrix{matrix} {}

  [[nodiscard]] Colour
  colourAtObject(const Object *shape,
                 const Vec4 &worldPoint) const noexcept override;
  [[nodiscard]] Colour colourAt(const Vec4 &point) const noexcept override {
    const auto temp = static_cast<int>(std::floor(point.x)) % 2 == 0 ? a : b;
    return temp;
  }

  [[nodiscard]] Matrix getTransformationMatrix() const noexcept override {
    return transformationMatrix;
  }
  void setTransformationMatrix(const Matrix &matrix) noexcept override {
    transformationMatrix = matrix;
  }

  [[nodiscard]] std::unique_ptr<Pattern> clone() const noexcept override {
    return std::make_unique<StripePattern>(*this);
  }

private:
  Matrix transformationMatrix;
};
} // namespace rtc
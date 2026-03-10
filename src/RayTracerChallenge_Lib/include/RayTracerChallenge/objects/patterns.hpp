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

  [[nodiscard]] virtual Colour patternAt(const Vec4 &point) const noexcept = 0;
  [[nodiscard]] virtual Matrix getTransformationMatrix() const noexcept = 0;
  virtual void setTransformationMatrix(const Matrix &matrix) noexcept = 0;
  [[nodiscard]] virtual std::unique_ptr<Pattern> clone() const noexcept = 0;

  [[nodiscard]] Colour patternAtObject(const Object *shape,
                                       const Vec4 &worldPoint) const noexcept;
};

class StripePattern : public Pattern {
public:
  Colour a;
  Colour b;

  StripePattern(const Colour &a, const Colour &b)
      : a{a}, b{b}, transformationMatrix{identity(4)} {}
  StripePattern(const Colour &a, const Colour &b, const Matrix &matrix)
      : a{a}, b{b}, transformationMatrix{matrix} {}

  [[nodiscard]] Colour patternAt(const Vec4 &point) const noexcept override {
    return static_cast<int>(std::floor(point.x)) % 2 == 0 ? a : b;
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

class GradientPattern : public Pattern {
public:
  Colour a;
  Colour b;

  GradientPattern(const Colour &a, const Colour &b)
      : a{a}, b{b}, transformationMatrix{identity(4)} {}
  GradientPattern(const Colour &a, const Colour &b, const Matrix &matrix)
      : a{a}, b{b}, transformationMatrix{matrix} {}

  [[nodiscard]] Colour patternAt(const Vec4 &point) const noexcept override {
    const auto distance = b - a;
    const auto fraction = point.x - std::floor(point.x);
    return a + distance * fraction;
  }

  [[nodiscard]] Matrix getTransformationMatrix() const noexcept override {
    return transformationMatrix;
  }
  void setTransformationMatrix(const Matrix &matrix) noexcept override {
    transformationMatrix = matrix;
  }

  [[nodiscard]] std::unique_ptr<Pattern> clone() const noexcept override {
    return std::make_unique<GradientPattern>(*this);
  }

private:
  Matrix transformationMatrix;
};

class RingPattern : public Pattern {
public:
  Colour a;
  Colour b;

  RingPattern(const Colour &a, const Colour &b)
      : a{a}, b{b}, transformationMatrix{identity(4)} {}
  RingPattern(const Colour &a, const Colour &b, const Matrix &matrix)
      : a{a}, b{b}, transformationMatrix{matrix} {}

  [[nodiscard]] Colour patternAt(const Vec4 &point) const noexcept override {
    const auto c = static_cast<int>(
        std::floor(std::sqrt(point.x * point.x + point.z * point.z)));
    return c % 2 == 0 ? a : b;
  }

  [[nodiscard]] Matrix getTransformationMatrix() const noexcept override {
    return transformationMatrix;
  }
  void setTransformationMatrix(const Matrix &matrix) noexcept override {
    transformationMatrix = matrix;
  }

  [[nodiscard]] std::unique_ptr<Pattern> clone() const noexcept override {
    return std::make_unique<RingPattern>(*this);
  }

private:
  Matrix transformationMatrix;
};

class CheckerPattern : public Pattern {
public:
  Colour a;
  Colour b;

  CheckerPattern(const Colour &a, const Colour &b)
      : a{a}, b{b}, transformationMatrix{identity(4)} {}
  CheckerPattern(const Colour &a, const Colour &b, const Matrix &matrix)
      : a{a}, b{b}, transformationMatrix{matrix} {}

  [[nodiscard]] Colour patternAt(const Vec4 &point) const noexcept override {
    const auto c = static_cast<int>(std::floor(point.x) + std::floor(point.y) +
                                    std::floor(point.z));
    return c % 2 == 0 ? a : b;
  }

  [[nodiscard]] Matrix getTransformationMatrix() const noexcept override {
    return transformationMatrix;
  }
  void setTransformationMatrix(const Matrix &matrix) noexcept override {
    transformationMatrix = matrix;
  }

  [[nodiscard]] std::unique_ptr<Pattern> clone() const noexcept override {
    return std::make_unique<CheckerPattern>(*this);
  }

private:
  Matrix transformationMatrix;
};
} // namespace rtc
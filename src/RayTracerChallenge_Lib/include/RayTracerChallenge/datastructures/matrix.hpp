#pragma once

#include <RayTracerChallenge/datastructures/vec4.hpp>
#include <cmath>
#include <vector>

namespace rtc {
/// @brief An NxN matrix of floats, where N is the size of the matrix.
class Matrix {
public:
  explicit Matrix(const size_t size) {
    matrix_ = std::vector(size, std::vector<float>(size));
  }

  explicit Matrix(std::vector<std::vector<float>> &&matrix) : matrix_{matrix} {}

  explicit Matrix(const std::vector<std::vector<float>> &matrix)
      : matrix_{matrix} {}

  ~Matrix() = default;
  constexpr Matrix(const Matrix &) = default;
  constexpr Matrix(Matrix &&) = default;
  constexpr Matrix &operator=(const Matrix &) = default;
  constexpr Matrix &operator=(Matrix &&) = default;

  bool operator==(const Matrix &rhs) const;
  Matrix operator*(const Matrix &rhs) const;
  Vec4 operator*(const Vec4 &rhs) const;

  [[nodiscard]] float determinant() const;
  [[nodiscard]] float minor(const size_t row, const size_t column) const;
  [[nodiscard]] float cofactor(const size_t row, const size_t column) const;
  [[nodiscard]] Matrix transpose() const;
  [[nodiscard]] Matrix submatrix(const size_t row, const size_t column) const;
  [[nodiscard]] Matrix inverse() const;

  [[nodiscard]]
  float at(const size_t x, const size_t y) const {
    return matrix_[y][x];
  }

  void set(const size_t x, const size_t y, const float value) {
    matrix_[y][x] = value;
  }

  [[nodiscard]]
  bool invertible() const {
    return determinant() != 0.0f;
  }

  [[nodiscard]]
  size_t size() const {
    return matrix_.size();
  }

  //////////////////////
  /// FLUENT METHODS ///
  //////////////////////
  Matrix &rotateX(const float r);
  Matrix &rotateY(const float r);
  Matrix &rotateZ(const float r);
  Matrix &scale(const float x, const float y, const float z);
  Matrix &translate(const float x, const float y, const float z);

private:
  std::vector<std::vector<float>> matrix_;
};

inline Matrix translationMatrix(const float x, const float y, const float z) {
  return Matrix{std::vector<std::vector<float>>{
      {1, 0, 0, x}, {0, 1, 0, y}, {0, 0, 1, z}, {0, 0, 0, 1}}};
}

inline Matrix rotationMatrixX(const float r) {
  return Matrix{
      std::vector<std::vector<float>>{{1, 0, 0, 0},
                                      {0, std::cos(r), -std::sin(r), 0},
                                      {0, std::sin(r), std::cos(r), 0},
                                      {0, 0, 0, 1}}};
}

inline Matrix rotationMatrixY(const float r) {
  return Matrix{
      std::vector<std::vector<float>>{{std::cos(r), 0, std::sin(r), 0},
                                      {0, 1, 0, 0},
                                      {-std::sin(r), 0, std::cos(r), 0},
                                      {0, 0, 0, 1}}};
}

inline Matrix rotationMatrixZ(const float r) {
  return Matrix{
      std::vector<std::vector<float>>{{std::cos(r), -std::sin(r), 0, 0},
                                      {std::sin(r), std::cos(r), 0, 0},
                                      {0, 0, 1, 0},
                                      {0, 0, 0, 1}}};
}

inline Matrix shearingMatrix(const float xy, const float xz, const float yx,
                             const float yz, const float zx, const float zy) {
  return Matrix{std::vector<std::vector<float>>{
      {1, xy, xz, 0}, {yx, 1, yz, 0}, {zx, zy, 1, 0}, {0, 0, 0, 1}}};
}

inline Matrix scalingMatrix(const float x, const float y, const float z) {
  return Matrix{std::vector<std::vector<float>>{
      {x, 0, 0, 0}, {0, y, 0, 0}, {0, 0, z, 0}, {0, 0, 0, 1}}};
}

inline Matrix identity(const size_t size) {
  Matrix res{size};
  for (size_t y = 0; y < size; ++y) {
    for (size_t x = 0; x < size; ++x) {
      if (x == y) {
        res.set(x, y, 1);
        break;
      }
    }
  }
  return res;
}

inline Matrix viewTransform(const Vec4 &from, const Vec4 &to, const Vec4 &up) {
  const auto forward = (to - from).normalise();
  const auto upNormal = up.normalise();
  const auto left = forward.cross(upNormal);
  const auto trueUp = left.cross(forward);
  const auto orientation = Matrix{
      std::vector<std::vector<float>>{{left.x, left.y, left.z, 0},
                                      {trueUp.x, trueUp.y, trueUp.z, 0},
                                      {-forward.x, -forward.y, -forward.z, 0},
                                      {0, 0, 0, 1}}};
  return orientation * translationMatrix(-from.x, -from.y, -from.z);
}

} // namespace rtc

std::ostream &operator<<(std::ostream &os, const rtc::Matrix &m);

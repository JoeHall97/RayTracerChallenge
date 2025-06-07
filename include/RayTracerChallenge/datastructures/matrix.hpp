#pragma once
#include <cstddef>
#include <vector>

#include "coord_tuple.hpp"

/// @brief An NxN matrix of floats, where N is the size of the matrix.
class Matrix {
 public:
  size_t size{};

  Matrix() = default;

  explicit Matrix(const size_t size) : size{size} {
    matrix = std::vector(size, std::vector<float>(size));
  }

  explicit Matrix(std::vector<std::vector<float>> &&matrix)
      : size{matrix.size()}, matrix{matrix} {}

  bool operator==(const Matrix &rhs) const;
  Matrix operator*(const Matrix &rhs) const;
  CoordTuple operator*(const CoordTuple &rhs) const;

  float determinant() const;
  float minor(const size_t row, const size_t column) const;
  float cofactor(const size_t row, const size_t column) const;
  Matrix transpose() const;
  Matrix submatrix(const size_t row, const size_t column) const;
  Matrix inverse() const;

  [[nodiscard]] float at(const size_t x, const size_t y) const {
    return matrix[y][x];
  }

  void set(const size_t x, const size_t y, const float value) {
    matrix[y][x] = value;
  }

  bool invertible() const { return determinant() != 0; }

 private:
  std::vector<std::vector<float>> matrix;
};

std::ostream &operator<<(std::ostream &os, const Matrix &m);

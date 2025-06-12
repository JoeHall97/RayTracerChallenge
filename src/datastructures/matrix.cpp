#include "matrix.hpp"

#include <cstddef>
#include <ostream>

#include "helpers.h"

/// @brief Calculates the multiplication of a and b, for the given row and
/// column.
/// @param a Matrix a.
/// @param b Matrix b.
/// @param row The row of matrix a to use when multiplying.
/// @param column The column of matrix b to use when multiplying.
/// @returns The value of the multiplied matrices.
inline float calcMatrixMultiply(const Matrix &a, const Matrix &b,
                                const size_t row, const size_t column) {
  float res = 0;
  for (size_t i = 0; i < a.size; ++i) {
    res += a.at(i, row) * b.at(column, i);
  }
  return res;
}

/// @brief Multiplies the two matrices, returning the result as a 2d vector.
/// @param lhs The left hand side matrix.
/// @param rhs The right hand side matrix.
inline std::vector<std::vector<float>> multiplyMatricesInPlace(
    const Matrix &lhs, const Matrix &rhs) {
  auto res = std::vector(lhs.size, std::vector<float>(lhs.size));
  if (lhs.size != rhs.size) return res;

  for (size_t y = 0; y < lhs.size; ++y) {
    for (size_t x = 0; x < lhs.size; ++x) {
      res[y][x] = calcMatrixMultiply(lhs, rhs, y, x);
    }
  }

  return res;
}

bool Matrix::operator==(const Matrix &rhs) const {
  if (size != rhs.size) return false;

  for (size_t y = 0; y < size; ++y) {
    for (size_t x = 0; x < size; ++x) {
      if (!areFloatsEqual(at(x, y), rhs.at(x, y))) {
        return false;
      }
    }
  }

  return true;
}

Matrix Matrix::operator*(const Matrix &rhs) const {
  if (size != rhs.size) return Matrix{};

  Matrix res{size};

  for (size_t row = 0; row < size; ++row) {
    for (size_t column = 0; column < size; ++column) {
      res.set(column, row, calcMatrixMultiply(*this, rhs, row, column));
    }
  }

  return res;
}

CoordTuple Matrix::operator*(const CoordTuple &rhs) const {
  if (size != 4) return CoordTuple{};

  return CoordTuple{rhs.x * matrix[0][0] + rhs.y * matrix[0][1] +
                        rhs.z * matrix[0][2] + rhs.w * matrix[0][3],
                    rhs.x * matrix[1][0] + rhs.y * matrix[1][1] +
                        rhs.z * matrix[1][2] + rhs.w * matrix[1][3],
                    rhs.x * matrix[2][0] + rhs.y * matrix[2][1] +
                        rhs.z * matrix[2][2] + rhs.w * matrix[2][3],
                    rhs.x * matrix[3][0] + rhs.y * matrix[3][1] +
                        rhs.z * matrix[3][2] + rhs.w * matrix[3][3]};
}

float Matrix::determinant() const {
  if (size == 2) return at(0, 0) * at(1, 1) - at(1, 0) * at(0, 1);

  float res = 0;
  for (size_t col = 0; col < size; ++col) {
    res += at(col, 0) * cofactor(0, col);
  }
  return res;
}

float Matrix::minor(const size_t row, const size_t column) const {
  return submatrix(row, column).determinant();
}

float Matrix::cofactor(const size_t row, const size_t column) const {
  Matrix res{size - 1};

  size_t resRow = 0, resCol = 0;
  for (size_t i = 0; i < size; ++i) {
    if (i == row) continue;
    for (size_t j = 0; j < size; ++j) {
      if (j == column) continue;
      res.set(resCol++, resRow, (i + j) % 2 == 0 ? at(j, i) : -at(j, i));
    }
    resCol = 0;
    ++resRow;
  }
  return res.determinant();
}

Matrix Matrix::transpose() const {
  Matrix res{size};

  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      res.set(j, i, at(i, j));
    }
  }

  return res;
}

Matrix Matrix::submatrix(const size_t row, const size_t column) const {
  Matrix res{size - 1};

  size_t resRow = 0, resCol = 0;
  for (size_t i = 0; i < size; ++i) {
    if (i == row) continue;
    for (size_t j = 0; j < size; ++j) {
      if (j == column) continue;
      res.set(resCol++, resRow, at(j, i));
    }
    resCol = 0;
    ++resRow;
  }

  return res;
}

Matrix Matrix::inverse() const {
  Matrix res{size};
  if (!invertible()) return res;

  for (size_t row = 0; row < size; ++row) {
    for (size_t col = 0; col < size; ++col) {
      const auto c = cofactor(row, col);
      // transpose and set
      res.set(row, col, c / determinant());
    }
  }

  return res;
}

Matrix &Matrix::rotateX(const float r) {
  matrix = multiplyMatricesInPlace(*this, rotationMatrixX(r));
  return *this;
}

Matrix &Matrix::rotateY(const float r) {
  matrix = multiplyMatricesInPlace(*this, rotationMatrixY(r));
  return *this;
}

Matrix &Matrix::rotateZ(const float r) {
  matrix = multiplyMatricesInPlace(*this, rotationMatrixZ(r));
  return *this;
}

Matrix &Matrix::scale(const float x, const float y, const float z) {
  matrix = multiplyMatricesInPlace(*this, scalingMatrix(x, y, z));
  return *this;
}

Matrix &Matrix::translate(const float x, const float y, const float z) {
  matrix = multiplyMatricesInPlace(*this, translationMatrix(x, y, z));
  return *this;
}

std::ostream &operator<<(std::ostream &os, const Matrix &m) {
  for (size_t i = 0; i < m.size; ++i) {
    os << "{ ";
    for (size_t j = 0; j < m.size; ++j) {
      os << m.at(j, i) << ", ";
    }
    os << "}\n";
  }

  return os;
}

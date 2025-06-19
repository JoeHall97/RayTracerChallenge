#pragma once
#include <cmath>
#include <vector>

#include "coord_tuple.hpp"

namespace rtc {
    /// @brief An NxN matrix of floats, where N is the size of the matrix.
    class Matrix {
    public:
        const size_t size;

        explicit Matrix(const size_t size) : size{size} {
            matrix_ = std::vector(size, std::vector<float>(size));
        }

        explicit Matrix(std::vector<std::vector<float>> &&matrix) : size{matrix.size()}, matrix_{matrix} {
        }

        bool operator==(const Matrix &rhs) const;
        Matrix operator*(const Matrix &rhs) const;
        CoordTuple operator*(const CoordTuple &rhs) const;

        [[nodiscard]] float determinant() const;
        [[nodiscard]] float minor(const size_t row, const size_t column) const;
        [[nodiscard]] float cofactor(const size_t row, const size_t column) const;
        [[nodiscard]] Matrix transpose() const;
        [[nodiscard]] Matrix submatrix(const size_t row, const size_t column) const;
        [[nodiscard]] Matrix inverse() const;

        //////////////////////
        /// FLUENT METHODS ///
        //////////////////////

        Matrix &rotateX(const float r);
        Matrix &rotateY(const float r);
        Matrix &rotateZ(const float r);
        Matrix &scale(const float x, const float y, const float z);
        Matrix &translate(const float x, const float y, const float z);

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

    private:
        std::vector<std::vector<float>> matrix_;
    };

    inline Matrix translationMatrix(const float x, const float y, const float z) {
        return Matrix{std::vector<std::vector<float>>{{1, 0, 0, x}, {0, 1, 0, y}, {0, 0, 1, z}, {0, 0, 0, 1}}};
    }

    inline Matrix rotationMatrixX(const float r) {
        return Matrix{std::vector<std::vector<float>>{
                {1, 0, 0, 0}, {0, std::cos(r), -std::sin(r), 0}, {0, std::sin(r), std::cos(r), 0}, {0, 0, 0, 1}}};
    }

    inline Matrix rotationMatrixY(const float r) {
        return Matrix{std::vector<std::vector<float>>{
                {std::cos(r), 0, std::sin(r), 0}, {0, 1, 0, 0}, {-std::sin(r), 0, std::cos(r), 0}, {0, 0, 0, 1}}};
    }

    inline Matrix rotationMatrixZ(const float r) {
        return Matrix{std::vector<std::vector<float>>{
                {std::cos(r), -std::sin(r), 0, 0}, {std::sin(r), std::cos(r), 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};
    }

    inline Matrix shearingMatrix(const float xy, const float xz, const float yx, const float yz, const float zx,
                                 const float zy) {
        return Matrix{std::vector<std::vector<float>>{{1, xy, xz, 0}, {yx, 1, yz, 0}, {zx, zy, 1, 0}, {0, 0, 0, 1}}};
    }

    inline Matrix scalingMatrix(const float x, const float y, const float z) {
        return Matrix{std::vector<std::vector<float>>{{x, 0, 0, 0}, {0, y, 0, 0}, {0, 0, z, 0}, {0, 0, 0, 1}}};
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

} // namespace rtc

std::ostream &operator<<(std::ostream &os, const rtc::Matrix &m);

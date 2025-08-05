#include <RayTracerChallenge/datastructures/matrix.hpp>
#include <RayTracerChallenge/datastructures/vec4.hpp>
#include <RayTracerChallenge/helpers/helpers.hpp>
#include <catch2/catch_test_macros.hpp>
#include <numbers>
#include <string>
#include <vector>

using rtc::Matrix, rtc::translationMatrix, rtc::shearingMatrix,
    rtc::scalingMatrix, rtc::rotationMatrixX, rtc::rotationMatrixY,
    rtc::rotationMatrixZ, rtc::Vec4, rtc::point, rtc::vector;

SCENARIO("Construct a 4x4 matrix.") {
  const std::string matrixString = "|  1   |  2   |  3   |  4   |\n"
                                   "|  5.5 |  6.5 |  7.5 |  8.5 |\n"
                                   "|  9   | 10   | 11   | 12   |\n"
                                   "| 13.5 | 14.5 | 15.5 | 16.5 |";
  GIVEN("A 4x4 matrix m:\n" + matrixString) {
    const Matrix m{std::vector<std::vector<float>>{{1, 2, 3, 4},
                                                   {5.5, 6.5, 7.5, 8.5},
                                                   {9, 10, 11, 12},
                                                   {13.5, 14.5, 15.5, 16.5}}};

    THEN("m[0, 0] = 1")
    AND_THEN("m[0, 3] = 4")
    AND_THEN("m[1, 0] = 5.5")
    AND_THEN("m[1, 2] = 7.5")
    AND_THEN("m[2, 2] = 11")
    AND_THEN("m[3, 0] = 13.5")
    AND_THEN("m[3, 2] = 15.5") {
      CHECK(m.at(0, 0) == 1);
      CHECK(m.at(3, 0) == 4);
      CHECK(m.at(0, 1) == 5.5);
      CHECK(m.at(2, 1) == 7.5);
      CHECK(m.at(2, 2) == 11);
      CHECK(m.at(0, 3) == 13.5);
      CHECK(m.at(2, 3) == 15.5);
    }
  }
}

SCENARIO("Matrix equality for identical and non-identical matrices.") {
  std::string matrixStringA = "|  1 |  2 |  3 |  4 |\n"
                              "|  5 |  6 |  7 |  8 |\n"
                              "|  9 | 10 | 11 | 12 |\n"
                              "| 13 | 14 | 15 | 16 |";
  std::string matrixStringB = "|  1 |  2 |  3 |  4 |\n"
                              "|  5 |  6 |  7 |  8 |\n"
                              "|  9 | 10 | 11 | 12 |\n"
                              "| 13 | 14 | 15 | 16 |";
  GIVEN("matrix a:\n" + matrixStringA)
  AND_GIVEN("matrix b:\n" + matrixStringB) {
    const Matrix a{std::vector<std::vector<float>>{
        {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}}};
    const Matrix b{std::vector<std::vector<float>>{
        {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}}};
    THEN("a = b") { CHECK(a == b); }
  }

  matrixStringA = "|  1 |  2 |  3 |  4 |\n"
                  "|  5 |  6 |  7 |  8 |\n"
                  "|  9 | 10 | 11 | 12 |\n"
                  "| 13 | 14 | 15 | 16 |";
  matrixStringB = "|  2 |  2 |  3 |  4 |\n"
                  "|  5 |  6 |  7 |  8 |\n"
                  "|  9 | 51 | 11 | 12 |\n"
                  "| 13 | 14 | 45 | 16 |";
  GIVEN("matrix a:\n" + matrixStringA)
  AND_GIVEN("matrix b:\n" + matrixStringB) {
    Matrix a{std::vector<std::vector<float>>{
        {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}}};
    Matrix b{std::vector<std::vector<float>>{
        {2, 2, 3, 4}, {5, 6, 7, 8}, {9, 51, 11, 12}, {13, 14, 45, 16}}};
    THEN("a != b") { CHECK(a != b); }
  }
}

SCENARIO("Multiplying two matrices.") {
  const std::string matrixStringA = "| 1 | 2 | 3 | 4 |\n"
                                    "| 5 | 6 | 7 | 8 |\n"
                                    "| 9 | 8 | 7 | 6 |\n"
                                    "| 5 | 4 | 3 | 2 |";
  const std::string matrixStringB = "| -2 |  1 |  2 |  3 |\n"
                                    "|  3 |  2 |  1 | -1 |\n"
                                    "|  4 |  3 |  6 |  5 |\n"
                                    "|  1 |  2 |  7 |  8 |";
  GIVEN("matrix a:\n" + matrixStringA)
  AND_GIVEN("matrix b:\n" + matrixStringB) {
    const Matrix a{std::vector<std::vector<float>>{
        {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}}};
    const Matrix b{std::vector<std::vector<float>>{
        {-2, 1, 2, 3}, {3, 2, 1, -1}, {4, 3, 6, 5}, {1, 2, 7, 8}}};
    const std::string matrixStringExpect = "| 20 |  22 |  50 |  48 |\n"
                                           "| 44 |  54 | 114 | 108 |\n"
                                           "| 40 |  58 | 110 | 102 |\n"
                                           "| 16 |  26 |  46 |  42 |";
    THEN("a * b is the following matrix:\n" + matrixStringExpect) {
      Matrix expect{std::vector<std::vector<float>>{{20, 22, 50, 48},
                                                    {44, 54, 114, 108},
                                                    {40, 58, 110, 102},
                                                    {16, 26, 46, 42}}};
      REQUIRE(a * b == expect);
    }
  }
}

SCENARIO("Multiplying a matrix by a tuple.") {
  const std::string matrixStringA = "| 1 | 2 | 3 | 4 |\n"
                                    "| 2 | 4 | 4 | 2 |\n"
                                    "| 8 | 6 | 4 | 1 |\n"
                                    "| 0 | 0 | 0 | 1 |";
  GIVEN("matrix a:\n" + matrixStringA)
  AND_GIVEN("b = tuple(1, 2, 3, 1)") {
    const Matrix a{std::vector<std::vector<float>>{
        {1, 2, 3, 4}, {2, 4, 4, 2}, {8, 6, 4, 1}, {0, 0, 0, 1}}};
    const Vec4 b{1, 2, 3, 1};
    THEN("a * b = tuple(18, 24, 33, 1)") {
      REQUIRE(a * b == Vec4{18, 24, 33, 1});
    }
  }
}

SCENARIO("Multiplying a matrix by the identity matrix.") {
  const std::string matrixStringA = "| 0 | 1 |  2 | 4 |\n"
                                    "| 2 | 4 |  4 | 8 |\n"
                                    "| 8 | 6 |  4 | 1 |\n"
                                    "| 4 | 3 | 10 | 1 |";
  GIVEN("matrix a:\n" + matrixStringA) {
    const Matrix a{std::vector<std::vector<float>>{
        {0, 1, 2, 4}, {2, 4, 4, 8}, {8, 6, 4, 1}, {4, 3, 10, 1}}};
    THEN("a * identity = a") {
      const Matrix identity{std::vector<std::vector<float>>{
          {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};
      REQUIRE(a * identity == a);
    }
  }
}

SCENARIO("Transpose a matrix.") {
  const std::string matrixStringA = "| 0 | 1 |  2 | 4 |\n"
                                    "| 2 | 4 |  4 | 8 |\n"
                                    "| 8 | 6 |  4 | 1 |\n"
                                    "| 4 | 3 | 10 | 1 |";
  GIVEN("matrix a:\n" + matrixStringA) {
    const Matrix a{std::vector<std::vector<float>>{
        {0, 1, 2, 4}, {2, 4, 4, 8}, {8, 6, 4, 1}, {4, 3, 10, 1}}};
    const std::string matrixStringTranspose = "| 0 | 2 | 8 |  4 |\n"
                                              "| 1 | 4 | 6 |  3 |\n"
                                              "| 2 | 4 | 4 | 10 |\n"
                                              "| 4 | 8 | 1 |  1 |";
    THEN("transpose(a) is the following:\n" + matrixStringTranspose) {
      const Matrix expect{std::vector<std::vector<float>>{
          {0, 2, 8, 4}, {1, 4, 6, 3}, {2, 4, 4, 10}, {4, 8, 1, 1}}};
      REQUIRE(a.transpose() == expect);
    }
  }
}

SCENARIO("Calculate the determinant of a 2x2 matrix") {
  GIVEN("the following matrix a:\n|  1 | 5 |\n| -3 | 2 |") {
    Matrix a{std::vector<std::vector<float>>{{1, 5}, {-3, 2}}};
    THEN("a.determinant() = 17") { REQUIRE(a.determinant() == 17); }
  }
}

SCENARIO("A submatrix of a 3x3 matrix is a 2x2 matrix") {
  const std::string matrixA = "|  1 | 5 |  0 |\n"
                              "| -3 | 2 |  7 |\n"
                              "|  0 | 6 | -3 |";
  GIVEN("the following matrix a:\n" + matrixA) {
    Matrix a{
        std::vector<std::vector<float>>{{1, 5, 0}, {-3, 2, 7}, {0, 6, -3}}};
    THEN(
        "a.submatrix(0,2) is the following matrix:\n| -3 | 2 |\n|  0 | 6 |\n") {
      Matrix expect{std::vector<std::vector<float>>{{-3, 2}, {0, 6}}};
      REQUIRE(a.submatrix(0, 2) == expect);
    }
  }
}

SCENARIO("A submatrix of a 4x4 matrix is a 3x3 matrix") {
  const std::string matrixA = "| -6 | 1 |  1 | 6 |\n"
                              "| -8 | 5 |  6 | 8 |\n"
                              "| -1 | 0 |  8 | 2 |\n"
                              "| -7 | 1 | -1 | 1 |";
  GIVEN("the following matrix a:\n" + matrixA) {
    Matrix a{std::vector<std::vector<float>>{
        {-6, 1, 1, 6}, {-8, 5, 6, 8}, {-1, 0, 8, 2}, {-7, 1, -1, 1}}};
    const std::string matrixB = "| -6 |  1 | 6 |\n"
                                "| -8 |  6 | 8 |\n"
                                "| -7 | -1 | 1 |";
    THEN("a.submatrix(2, 1) is the following:\n" + matrixB) {
      Matrix expect{
          std::vector<std::vector<float>>{{-6, 1, 6}, {-8, 6, 8}, {-7, -1, 1}}};
      REQUIRE(a.submatrix(2, 1) == expect);
    }
  }
}

SCENARIO("Calculate the minor of a 3x3 matrix.") {
  const std::string matrixStringA = "| 3 |  5 |  0 |\n"
                                    "| 2 | -1 | -7 |\n"
                                    "| 6 | -1 |  5 |";
  GIVEN("the following 3x3 matrix a:\n" + matrixStringA)
  AND_GIVEN("b = a.submatrix(1, 0)") {
    Matrix a{
        std::vector<std::vector<float>>{{3, 5, 0}, {2, -1, -7}, {6, -1, 5}}};
    auto b = a.submatrix(1, 0);
    THEN("a.minor(1, 0) = b.determinant()") {
      REQUIRE(a.minor(1, 0) == b.determinant());
    }
  }
}

SCENARIO("Calculate the cofactor of a 3x3 matrix.") {
  const std::string matrixStringA = "| 3 |  5 |  0 |\n"
                                    "| 2 | -1 | -7 |\n"
                                    "| 6 | -1 |  5 |";
  GIVEN("the following 3x3 matrix a:\n" + matrixStringA) {
    Matrix a{
        std::vector<std::vector<float>>{{3, 5, 0}, {2, -1, -7}, {6, -1, 5}}};
    THEN("a.minor(0, 0) = -12")
    AND_THEN("a.cofactor(0, 0) = -12")
    AND_THEN("a.minor(1, 0) = 25")
    AND_THEN("a.cofactor(1, 0) = -12")
    AND_THEN("a.minor(2, 0) = -35")
    AND_THEN("a.cofactor(2, 0) = -35")
    AND_THEN("a.minor(0, 1) = 52")
    AND_THEN("a.cofactor(0, 1) = -52")
    AND_THEN("a.minor(1, 1) = 15")
    AND_THEN("a.cofactor(1, 1) = 15")
    AND_THEN("a.minor(2, 1) = -21")
    AND_THEN("a.cofactor(2, 1) = 21")
    AND_THEN("a.minor(0, 2) = 4")
    AND_THEN("a.cofactor(0, 2) = 4")
    AND_THEN("a.minor(1, 2) = -33")
    AND_THEN("a.cofactor(1, 2) = 33")
    AND_THEN("a.minor(2, 2) = -13")
    AND_THEN("a.cofactor(2, 2) = -13") {
      CHECK(a.minor(0, 0) == -12);
      REQUIRE(a.cofactor(0, 0) == -12);
      CHECK(a.minor(1, 0) == 25);
      REQUIRE(a.cofactor(1, 0) == -25);
      CHECK(a.minor(2, 0) == -35);
      REQUIRE(a.cofactor(2, 0) == -35);

      CHECK(a.minor(0, 1) == 52);
      REQUIRE(a.cofactor(0, 1) == -52);
      CHECK(a.minor(1, 1) == 15);
      REQUIRE(a.cofactor(1, 1) == 15);
      CHECK(a.minor(2, 1) == -21);
      REQUIRE(a.cofactor(2, 1) == 21);

      CHECK(a.minor(0, 2) == 4);
      REQUIRE(a.cofactor(0, 2) == 4);
      CHECK(a.minor(1, 2) == -33);
      REQUIRE(a.cofactor(1, 2) == 33);
      CHECK(a.minor(2, 2) == -13);
      REQUIRE(a.cofactor(2, 2) == -13);
    }
  }
}

SCENARIO("Calculating the determinant of a 3x3 matrix.") {
  const std::string matrixStringA = "|  1 | 2 |  6 |\n"
                                    "| -5 | 8 | -4 |\n"
                                    "|  2 | 6 |  4 |";
  GIVEN("the following 3x3 matrix a:\n" + matrixStringA) {
    Matrix a{
        std::vector<std::vector<float>>{{1, 2, 6}, {-5, 8, -4}, {2, 6, 4}}};

    THEN("a.cofactor(0, 0) = 56")
    AND_THEN("a.cofactor(0, 1) = 12")
    AND_THEN("a.cofactor(0, 2) = -46")
    AND_THEN("a.determinant() == -196") {
      CHECK(a.cofactor(0, 0) == 56);
      CHECK(a.cofactor(0, 1) == 12);
      CHECK(a.cofactor(0, 2) == -46);
      REQUIRE(a.determinant() == -196);
    }
  }
}

SCENARIO("Calculate the determinant of a 4x4 matrix.") {
  const std::string matrixStringA = "| -2 | -8 |  3 |  5 |\n"
                                    "| -3 |  1 |  7 |  3 |\n"
                                    "|  1 |  2 | -9 |  6 |\n"
                                    "| -6 |  7 |  7 | -9 |";
  GIVEN("the following 4x4 matrix a:\n") {
    Matrix a{std::vector<std::vector<float>>{
        {-2, -8, 3, 5}, {-3, 1, 7, 3}, {1, 2, -9, 6}, {-6, 7, 7, -9}}};
    THEN("a.cofactor(0, 0) = 690")
    AND_THEN("a.cofactor(0, 1) = 447")
    AND_THEN("a.cofactor(0, 2) = 210")
    AND_THEN("a.cofactor(0, 3) = 51")
    AND_THEN("a.determinant() = -4071") {
      CHECK(a.cofactor(0, 0) == 690);
      CHECK(a.cofactor(0, 1) == 447);
      CHECK(a.cofactor(0, 2) == 210);
      CHECK(a.cofactor(0, 3) == 51);
      REQUIRE(a.determinant() == -4071);
    }
  }
}

SCENARIO("Testing a matrix for invertability.") {
  std::string matrixStringA = "| 6 |  4 | 4 |  4 |\n"
                              "| 5 |  5 | 7 |  6 |\n"
                              "| 4 | -9 | 3 | -7 |\n"
                              "| 9 |  1 | 7 | -6 |";
  GIVEN("the following 4x4 matrix a:\n" + matrixStringA) {
    Matrix a{std::vector<std::vector<float>>{
        {6, 4, 4, 4}, {5, 5, 7, 6}, {4, -9, 3, -7}, {9, 1, 7, -6}}};
    THEN("a.determinant() = -2120")
    AND_THEN("a is invertible") {
      CHECK(a.determinant() == -2120);
      REQUIRE(a.invertible());
    }
  }

  matrixStringA = "| -4 |  2 | -2 | -3 |\n"
                  "|  9 |  6 |  2 |  6 |\n"
                  "|  0 | -5 |  1 | -5 |\n"
                  "|  0 |  0 |  0 |  0 |";
  GIVEN("the following 4x4 matrix a:\n" + matrixStringA) {
    Matrix a{std::vector<std::vector<float>>{
        {-4, 2, -2, -3}, {9, 6, 2, 6}, {0, -5, 1, -5}, {0, 0, 0, 0}}};
    THEN("a.determinant() = 0")
    AND_THEN("a is not invertible") {
      CHECK(a.determinant() == 0);
      REQUIRE(!a.invertible());
    }
  }
}

SCENARIO("Calculating the inverse of a matrix") {
  std::string matrixStringA = "| -5 |  2 |  6 | -8 |\n"
                              "|  1 | -5 |  1 |  8 |\n"
                              "|  7 |  7 | -6 | -7 |\n"
                              "|  1 | -3 |  7 |  4 |";
  GIVEN("the following 4x4 matrix a:\n" + matrixStringA)
  AND_GIVEN("b = a.inverse()") {
    Matrix a{std::vector<std::vector<float>>{
        {-5, 2, 6, -8}, {1, -5, 1, 8}, {7, 7, -6, -7}, {1, -3, 7, 4}}};
    auto b = a.inverse();

    const std::string matrixStringB =
        "|  0.21805 |  0.45113 |  0.24060 | -0.04511 |\n"
        "| -0.80827 | -1.45677 | -0.44361 |  0.52068 |\n"
        "| -0.07895 | -0.22368 | -0.05263 |  0.19737 |\n"
        "| -0.52256 | -0.81391 | -0.30075 |  0.30639 |";

    THEN("a.determinant() = 532")
    AND_THEN("a.cofactor(2, 3) = -160")
    AND_THEN("b[3, 2] = -160/532")
    AND_THEN("a.cofactor(3, 2) = 105")
    AND_THEN("b[2, 3] = 105/532")
    AND_THEN("b is the following 4x4 matrix:\n" + matrixStringB) {
      CHECK(a.determinant() == 532);
      CHECK(a.cofactor(2, 3) == -160);
      CHECK(rtc::areFloatsEqual(b.at(2, 3), -160.0 / 532.0));
      CHECK(a.cofactor(3, 2) == 105);
      CHECK(rtc::areFloatsEqual(b.at(3, 2), 105.0 / 532.0));

      const Matrix expect{std::vector<std::vector<float>>{
          {0.21805, 0.45113, 0.24060, -0.04511},
          {-0.80827, -1.45677, -0.44361, 0.52068},
          {-0.07895, -0.22368, -0.05263, 0.19737},
          {-0.52256, -0.81391, -0.30075, 0.30639}}};
      REQUIRE(b == expect);
    }
  }

  matrixStringA = "|  8 | -5 |  9 |  2 |\n"
                  "|  7 |  5 |  6 |  1 |\n"
                  "| -6 |  0 |  9 |  6 |\n"
                  "| -3 |  0 | -9 | -4 |";
  GIVEN("the following 4x4 matrix a:\n" + matrixStringA) {
    const Matrix a{std::vector<std::vector<float>>{
        {8, -5, 9, 2}, {7, 5, 6, 1}, {-6, 0, 9, 6}, {-3, 0, -9, -4}}};
    const std::string matrixStringExpect =
        "| -0.15385 | -0.15385 | -0.28205 | -0.53846 |\n"
        "| -0.07692 |  0.12308 |  0.02564 |  0.03077 |\n"
        "|  0.35897 |  0.35897 |  0.43590 |  0.92308 |\n"
        "| -0.69231 | -0.69231 | -0.76923 | -1.92308 |";
    THEN("a.inverse() is the following 4x4 matrix:\n" + matrixStringExpect) {
      const Matrix expect{std::vector<std::vector<float>>{
          {-0.15385, -0.15385, -0.28205, -0.53846},
          {-0.07692, 0.12308, 0.02564, 0.03077},
          {0.35897, 0.35897, 0.43590, 0.92308},
          {-0.69231, -0.69231, -0.76923, -1.92308}}};
      REQUIRE(a.inverse() == expect);
    }
  }

  matrixStringA = "|  9 |  3 |  0 |  9 |\n"
                  "| -5 | -2 | -6 | -3 |\n"
                  "| -4 |  9 |  6 |  4 |\n"
                  "| -7 |  6 |  6 |  2 |";
  GIVEN("the following 4x4 matrix a:\n" + matrixStringA) {
    const Matrix a{std::vector<std::vector<float>>{
        {9, 3, 0, 9}, {-5, -2, -6, -3}, {-4, 9, 6, 4}, {-7, 6, 6, 2}}};
    const std::string matrixStringExpect =
        "| -0.04074 | -0.07778 |  0.14444 | -0.22222 |\n"
        "| -0.07778 |  0.03333 |  0.36667 | -0.33333 |\n"
        "| -0.02901 | -0.14630 | -0.10926 |  0.12963 |\n"
        "|  0.17778 |  0.06667 | -0.26667 |  0.33333 |";

    THEN("a.inverse() is the following 4x4 matrix:\n" + matrixStringExpect) {
      const Matrix expect{std::vector<std::vector<float>>{
          {-0.04074, -0.07778, 0.14444, -0.22222},
          {-0.07778, 0.03333, 0.36667, -0.33333},
          {-0.02901, -0.14630, -0.10926, 0.12963},
          {0.17778, 0.06667, -0.26667, 0.33333}}};
      REQUIRE(a.inverse() == expect);
    }
  }
}

SCENARIO("Multiplying a product by its inverse.") {
  const std::string matrixStringA = "|  3 | -9 |  7 |  3 |\n"
                                    "|  3 | -8 |  2 | -9 |\n"
                                    "| -4 |  4 |  4 |  1 |\n"
                                    "| -6 |  5 | -1 |  1 |";
  const std::string matrixStringB = "| 8 |  2 | 2 | 2 |\n"
                                    "| 3 | -1 | 7 | 0 |\n"
                                    "| 7 |  0 | 5 | 4 |\n"
                                    "| 6 | -2 | 0 | 5 |";
  GIVEN("the following matrix a:\n" + matrixStringA)
  AND_GIVEN("the following matrix b:\n" + matrixStringB)
  AND_GIVEN("c = a * b") {
    const Matrix a{std::vector<std::vector<float>>{
        {3, -9, 7, 3}, {3, -8, 2, -9}, {-4, 4, 4, 1}, {-6, 5, -1, 1}}};
    const Matrix b{std::vector<std::vector<float>>{
        {8, 2, 2, 2}, {3, -1, 7, 0}, {7, 0, 5, 4}, {6, -2, 0, 5}}};
    const auto c = a * b;
    THEN("c * b.inverse() = a") { REQUIRE(c * b.inverse() == a); }
  }
}

SCENARIO("Multiplying by a translation matrix.") {
  GIVEN("transform = translation(5, -3, 2)")
  AND_GIVEN("p = point(-3, 4, 5)") {
    const auto transform = translationMatrix(5, -3, 2);
    const auto p = point(-3, 4, 5);
    THEN("transform * p = point(2, 1, 7)") {
      REQUIRE(transform * p == point(2, 1, 7));
    }
  }
}

SCENARIO("Multiplying by the inverse of a translation matrix.") {
  GIVEN("transform = translation(5, -3, 2)")
  AND_GIVEN("inv = transform.inverse()")
  AND_GIVEN("p = point(-3, 4, 5)") {
    const auto inv = translationMatrix(5, -3, 2).inverse();
    const auto p = point(-3, 4, 5);
    THEN("inv * p = point(-8, 7, 3)") { REQUIRE(inv * p == point(-8, 7, 3)); }
  }
}

SCENARIO("Translation does not affect vectors.") {
  GIVEN("transform = translation(5, -3, 2)")
  AND_GIVEN("v = vector(-3, 4, 5)") {
    const auto transform = translationMatrix(5, -3, 2);
    const auto v = vector(-3, 4, 5);
    THEN("transform * v = v") { REQUIRE(transform * v == v); }
  }
}

SCENARIO("A scaling matrix applied to a point.") {
  GIVEN("transform = scaling(2, 3, 4)")
  AND_GIVEN("p = point(-4, 6, 8)") {
    const auto transform = scalingMatrix(2, 3, 4);
    const auto p = point(-4, 6, 8);
    THEN("transform * p = point(-8, 18, 32)") {
      REQUIRE(transform * p == point(-8, 18, 32));
    }
  }
}

SCENARIO("A scaling matrix applied to a vector.") {
  GIVEN("transform = scaling(2, 3, 4)")
  AND_GIVEN("v = vector(-4, 6, 8)") {
    const auto transform = scalingMatrix(2, 3, 4);
    const auto v = vector(-4, 6, 8);
    THEN("transform * v = vector(-8, 18, 32)") {
      REQUIRE(transform * v == vector(-8, 18, 32));
    }
  }
}

SCENARIO("Multiplying by the inverse of a scaling matrix.") {
  GIVEN("transform = scaling(2, 3, 4)")
  AND_GIVEN("inv = transform.inverse()")
  AND_GIVEN("v = vector(-4, 6, 8)") {
    const auto transform = scalingMatrix(2, 3, 4);
    const auto inv = transform.inverse();
    const auto v = vector(-4, 6, 8);
    THEN("inv * v = vector(-2, 2, 2)") { REQUIRE(inv * v == vector(-2, 2, 2)); }
  }
}

SCENARIO("Reelection is scaling by a negative value.") {
  GIVEN("transform = scaling(-1, 1, 1)")
  AND_GIVEN("p = point(-4, 6, 8)") {
    const auto transform = scalingMatrix(-1, 1, 1);
    const auto p = point(-4, 6, 8);
    THEN("transform * p = point(4, 6, 8)") {
      REQUIRE(transform * p == point(4, 6, 8));
    }
  }
}

SCENARIO("Rotating a point around the x axis.") {
  GIVEN("p = point(0, 1, 0)")
  AND_GIVEN("half_quarter = rotation_x(pi/4)")
  AND_GIVEN("full_quarter = rotation_x(pi/2)") {
    const auto p = point(0, 1, 0);
    const auto halfQuarter = rotationMatrixX(std::numbers::pi / 4);
    const auto fullQuarter = rotationMatrixX(std::numbers::pi / 2);

    THEN("half_quarter * p = point(0, sqrt(2)/2, sqrt(2)/2)")
    AND_THEN("full_quarter * p = point(0, 0, 1)") {
      REQUIRE(halfQuarter * p == point(0, sqrt(2) / 2, sqrt(2) / 2));
      REQUIRE(fullQuarter * p == point(0, 0, 1));
    }
  }
}

SCENARIO("The inverse of an x-rotation rotates in the opposite direction.") {
  GIVEN("p = point(0, 1, 0)")
  AND_GIVEN("half_quarter = rotation_x(pi/4)")
  AND_GIVEN("inv = half_quarter.inverse()") {
    const auto p = point(0, 1, 0);
    const auto half_quarter = rotationMatrixX(std::numbers::pi / 4);
    const auto inv = half_quarter.inverse();
    THEN("inv * p = point(0, sqrt(2)/2, sqrt(2)/2)") {
      REQUIRE(inv * p == point(0, sqrt(2) / 2, -sqrt(2) / 2));
    }
  }
}

SCENARIO("Rotating a point around the y axis.") {
  GIVEN("p = point(0, 0, 1)")
  AND_GIVEN("half_quarter = rotation_y(pi/4)")
  AND_GIVEN("full_quarter = rotation_y(pi/2)") {
    const auto p = point(0, 0, 1);
    const auto halfQuarter = rotationMatrixY(std::numbers::pi / 4);
    const auto fullQuarter = rotationMatrixY(std::numbers::pi / 2);

    THEN("half_quarter * p = point(sqrt(2)/2, 0, sqrt(2)/2)")
    AND_THEN("full_quarter * p = point(1, 0, 0)") {
      REQUIRE(halfQuarter * p == point(sqrt(2) / 2, 0, sqrt(2) / 2));
      REQUIRE(fullQuarter * p == point(1, 0, 0));
    }
  }
}

SCENARIO("Rotating a point around the z axis.") {
  GIVEN("p = point(0, 1, 0)")
  AND_GIVEN("half_quarter = rotation_z(pi/4)")
  AND_GIVEN("full_quarter = rotation_z(pi/2)") {
    const auto p = point(0, 1, 0);
    const auto halfQuarter = rotationMatrixZ(std::numbers::pi / 4);
    const auto fullQuarter = rotationMatrixZ(std::numbers::pi / 2);

    THEN("half_quarter * p = point(-sqrt(2)/2, sqrt(2)/2, 0)")
    AND_THEN("full_quarter * p = point(-1, 0, 0)") {
      REQUIRE(halfQuarter * p == point(-sqrt(2) / 2, sqrt(2) / 2, 0));
      REQUIRE(fullQuarter * p == point(-1, 0, 0));
    }
  }
}

SCENARIO("A shearing transformation moves x in proportion to y.") {
  GIVEN("transform = shearing(1, 0, 0, 0, 0, 0)")
  AND_GIVEN("p = point(2, 3, 4)") {
    const auto transform = shearingMatrix(1, 0, 0, 0, 0, 0);
    const auto p = point(2, 3, 4);
    THEN("transform * p = point(5, 3, 4)") {
      REQUIRE(transform * p == point(5, 3, 4));
    }
  }
}

SCENARIO("A shearing transformation moves x in proportion to z.") {
  GIVEN("transform = shearing(0, 1, 0, 0, 0, 0)")
  AND_GIVEN("p = point(2, 3, 4)") {
    const auto transform = shearingMatrix(0, 1, 0, 0, 0, 0);
    const auto p = point(2, 3, 4);
    THEN("transform * p = point(6, 3, 4)") {
      REQUIRE(transform * p == point(6, 3, 4));
    }
  }
}

SCENARIO("A shearing transformation moves y in proportion to x.") {
  GIVEN("transform = shearing(0, 0, 1, 0, 0, 0)")
  AND_GIVEN("p = point(2, 3, 4)") {
    const auto transform = shearingMatrix(0, 0, 1, 0, 0, 0);
    const auto p = point(2, 3, 4);
    THEN("transform * p = point(2, 5, 4)") {
      REQUIRE(transform * p == point(2, 5, 4));
    }
  }
}

SCENARIO("A shearing transformation moves y in proportion to z.") {
  GIVEN("transform = shearing(0, 0, 0, 1, 0, 0)")
  AND_GIVEN("p = point(2, 3, 4)") {
    const auto transform = shearingMatrix(0, 0, 0, 1, 0, 0);
    const auto p = point(2, 3, 4);
    THEN("transform * p = point(2, 7, 4)") {
      REQUIRE(transform * p == point(2, 7, 4));
    }
  }
}

SCENARIO("A shearing transformation moves z in proportion to x.") {
  GIVEN("transform = shearing(0, 0, 0, 0, 1, 0)")
  AND_GIVEN("p = point(2, 3, 4)") {
    const auto transform = shearingMatrix(0, 0, 0, 0, 1, 0);
    const auto p = point(2, 3, 4);
    THEN("transform * p = point(2, 3, 6)") {
      REQUIRE(transform * p == point(2, 3, 6));
    }
  }
}

SCENARIO("A shearing transformation moves z in proportion to y.") {
  GIVEN("transform = shearing(0, 0, 0, 0, 0, 1)")
  AND_GIVEN("p = point(2, 3, 4)") {
    const auto transform = shearingMatrix(0, 0, 0, 0, 0, 1);
    const auto p = point(2, 3, 4);
    THEN("transform * p = point(2, 3, 7)") {
      REQUIRE(transform * p == point(2, 3, 7));
    }
  }
}

SCENARIO("Chained transformations must be applied in reverse order.") {
  GIVEN("p = point(1, 0, 1)")
  AND_GIVEN("A = rotation_x(pi/2)")
  AND_GIVEN("B = scaling(5, 5, 5)")
  AND_GIVEN("C = translation(10, 5, 7)") {
    const auto p = point(1, 0, 1);
    THEN("T = C * B * A")
    AND_THEN("T * p = point(15, 0, 7)") {
      const auto T =
          rtc::identity(4).translate(10, 5, 7).scale(5, 5, 5).rotateX(
              std::numbers::pi / 2);
      const auto test = translationMatrix(10, 5, 7) * scalingMatrix(5, 5, 5) *
                        rotationMatrixX(std::numbers::pi / 2);
      CHECK(test * p == point(15, 0, 7));
      REQUIRE(T * p == point(15, 0, 7));
    }
  }
}

SCENARIO("The transformation matrix for the default orientation.") {
  GIVEN("from = point(0, 0, 0)")
  AND_GIVEN("to = point(0, 0, -1)")
  AND_GIVEN("up = vector(0, 1, 0)") {
    const auto from = point(0, 0, 0);
    const auto to = point(0, 0, -1);
    const auto up = vector(0, 1, 0);
    WHEN("t = viewTransform(from, to, up)") {
      const auto t = rtc::viewTransform(from, to, up);
      THEN("t = identityMatrix") { REQUIRE(t == rtc::identity(4)); }
    }
  }
}

SCENARIO("A view transformation matrix looking in the positive z direction.") {
  GIVEN("from = point(0, 0, 0)")
  AND_GIVEN("to = point(0, 0, 1)")
  AND_GIVEN("up = vector(0, 1, 0)") {
    const auto from = point(0, 0, 0);
    const auto to = point(0, 0, 1);
    const auto up = vector(0, 1, 0);
    WHEN("t = viewTransform(from, to, up)") {
      const auto t = rtc::viewTransform(from, to, up);
      THEN("t = scalingMatrix(-1, 1, -1)") {
        REQUIRE(t == rtc::scalingMatrix(-1, 1, -1));
      }
    }
  }
}

SCENARIO("The view transformation moves the world.") {
  GIVEN("from = point(0, 0, 8)")
  AND_GIVEN("to = point(0, 0, 0)")
  AND_GIVEN("up = vector(0, 1, 0)") {
    const auto from = point(0, 0, 8);
    const auto to = point(0, 0, 0);
    const auto up = vector(0, 1, 0);
    WHEN("t = viewTransform(from, to, up)") {
      const auto t = rtc::viewTransform(from, to, up);
      THEN("t = translationMatrix(0, 0, -8)") {
        REQUIRE(t == rtc::translationMatrix(0, 0, -8));
      }
    }
  }
}

SCENARIO("An arbitrary view transformation.") {
  GIVEN("from = point(1, 3, 2)")
  AND_GIVEN("to = point(4, -2, 8)")
  AND_GIVEN("up = vector(1, 1, 0)") {
    const auto from = point(1, 3, 2);
    const auto to = point(4, -2, 8);
    const auto up = vector(1, 1, 0);
    WHEN("t = viewTransform(from, to, up)") {
      const auto t = rtc::viewTransform(from, to, up);
      const std::string matrixString =
          "| -0.50709 | 0.50709 |  0.67612 | -2.36643 |"
          "|  0.76772 | 0.60609 |  0.12122 | -2.82843 |"
          "| -0.35857 | 0.59761 | -0.71714 |  0.00000 |"
          "|  0.00000 | 0.00000 |  0.00000 |  1.00000 |";
      THEN("t is the following 4x4 matrix: \n" + matrixString) {
        const Matrix matrix{std::vector<std::vector<float>>{
            {-0.50709f, 0.50709f, 0.67612f, -2.36643f},
            {0.76772f, 0.60609f, 0.12122f, -2.82843f},
            {-0.35857f, 0.59761f, -0.71714f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f},
        }};
        REQUIRE(t == matrix);
      }
    }
  }
}

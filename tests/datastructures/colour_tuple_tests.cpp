#include <catch2/catch_test_macros.hpp>

#include "colour_tuple.hpp"
#include "helpers.h"

SCENARIO("Colours are (red, green, blue) tuples.") {
  GIVEN("c = colour(-0.5, 0.4, 1.7)") {
    auto c = ColourTuple{-0.5, 0.4, 1.7};
    THEN("c.red = -0.5")
    AND_THEN("c.green = 0.4")
    AND_THEN("c.blue = 1.7") {
      REQUIRE(areFloatsEqual(c.red, -0.5));
      REQUIRE(areFloatsEqual(c.green, 0.4));
      REQUIRE(areFloatsEqual(c.blue, 1.7));
    }
  }
}

SCENARIO("Adding colours.") {
  GIVEN("c1 = colour(0.9, 0.6, 0.75)")
  AND_GIVEN("c2 = colour(0.7, 0.1, 0.25)") {
    auto c1 = ColourTuple{0.9, 0.6, 0.75};
    auto c2 = ColourTuple{0.7, 0.1, 0.25};
    THEN("c1 + c2 = colour(1.6, 0.7, 1.0)") {
      REQUIRE(c1 + c2 == ColourTuple{1.6, 0.7, 1.0});
    }
  }
}
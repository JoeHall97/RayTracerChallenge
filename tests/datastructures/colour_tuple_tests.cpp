#include <RayTracerChallenge/datastructures/colour_tuple.hpp>
#include <RayTracerChallenge/helpers/helpers.hpp>
#include <catch2/catch_test_macros.hpp>

SCENARIO("Colours are (red, green, blue) tuples.") {
    GIVEN("c = colour(-0.5, 0.4, 1.7)") {
        const auto c = rtc::ColourTuple{-0.5, 0.4, 1.7};
        THEN("c.red = -0.5")
        AND_THEN("c.green = 0.4")
        AND_THEN("c.blue = 1.7") {
            REQUIRE(rtc::areFloatsEqual(c.red, -0.5));
            REQUIRE(rtc::areFloatsEqual(c.green, 0.4));
            REQUIRE(rtc::areFloatsEqual(c.blue, 1.7));
        }
    }
}

SCENARIO("Adding colours.") {
    GIVEN("c1 = colour(0.9, 0.6, 0.75)")
    AND_GIVEN("c2 = colour(0.7, 0.1, 0.25)") {
        const auto c1 = rtc::ColourTuple{0.9, 0.6, 0.75};
        const auto c2 = rtc::ColourTuple{0.7, 0.1, 0.25};
        THEN("c1 + c2 = colour(1.6, 0.7, 1.0)") {
            REQUIRE(c1 + c2 == rtc::ColourTuple{1.6, 0.7, 1.0});
        }
    }
}

#include <RayTracerChallenge/objects/patterns.hpp>
#include <RayTracerChallenge/objects/sphere.hpp>
#include <catch2/catch_test_macros.hpp>

SCENARIO("A stripe pattern is constant in y") {
  GIVEN("pattern = stripePatter(white, black)") {
    const auto pattern = rtc::StripePattern{rtc::WHITE, rtc::BLACK};
    THEN("pattern.stripeAt(point(0, 0, 0)) = white")
    AND_THEN("pattern.stripeAt(point(0, 1, 0)) = white")
    AND_THEN("pattern.stripeAt(point(0, 2, 0)) = white") {
      CHECK(pattern.colourAt(rtc::point(0, 0, 0)) == rtc::WHITE);
      CHECK(pattern.colourAt(rtc::point(0, 1, 0)) == rtc::WHITE);
      CHECK(pattern.colourAt(rtc::point(0, 2, 0)) == rtc::WHITE);
    }
  }
}

SCENARIO("A stripe pattern is constant in z") {
  GIVEN("pattern = stripePatter(white, black)") {
    const auto pattern = rtc::StripePattern{rtc::WHITE, rtc::BLACK};
    THEN("pattern.stripeAt(point(0, 0, 0)) = white")
    AND_THEN("pattern.stripeAt(point(0, 0, 1)) = white")
    AND_THEN("pattern.stripeAt(point(0, 0, 2)) = white") {
      CHECK(pattern.colourAt(rtc::point(0, 0, 0)) == rtc::WHITE);
      CHECK(pattern.colourAt(rtc::point(0, 0, 1)) == rtc::WHITE);
      CHECK(pattern.colourAt(rtc::point(0, 0, 2)) == rtc::WHITE);
    }
  }
}

SCENARIO("A stripe pattern is constant in x") {
  GIVEN("pattern = stripePatter(white, black)") {
    const auto pattern = rtc::StripePattern{rtc::WHITE, rtc::BLACK};
    THEN("pattern.stripeAt(point(0, 0, 0)) = white")
    AND_THEN("pattern.stripeAt(point(0.9, 0, 0)) = white")
    AND_THEN("pattern.stripeAt(point(1, 0, 0)) = black")
    AND_THEN("pattern.stripeAt(point(-1, 0, 0)) = black")
    AND_THEN("pattern.stripeAt(point(-1.1, 0, 0)) = white")
    AND_THEN("pattern.stripeAt(point(-0.1, 0, 0)) = black") {
      CHECK(pattern.colourAt(rtc::point(0, 0, 0)) == rtc::WHITE);
      CHECK(pattern.colourAt(rtc::point(0.9, 0, 0)) == rtc::WHITE);
      CHECK(pattern.colourAt(rtc::point(1, 0, 0)) == rtc::BLACK);
      CHECK(pattern.colourAt(rtc::point(-1, 0, 0)) == rtc::BLACK);
      CHECK(pattern.colourAt(rtc::point(-1.1, 0, 0)) == rtc::WHITE);
      CHECK(pattern.colourAt(rtc::point(-0.1, 0, 0)) == rtc::BLACK);
    }
  }
}

SCENARIO("Stripes with an object transformation.") {
  GIVEN("object = sphere()")
  AND_GIVEN("object.transform = scaling(2, 2, 2)")
  AND_GIVEN("pattern = stripePattern(white, black)") {
    auto object = rtc::sphere();
    object.setTransformationMatrix(rtc::scalingMatrix(2, 2, 2));
    const auto pattern = rtc::StripePattern{rtc::WHITE, rtc::BLACK};
    WHEN("c = pattern.stripeAtObject(point(1.5, 0, 0))") {
      const auto c = pattern.colourAtObject(&object, rtc::point(1.5, 0, 0));
      THEN("c = white") { CHECK(c == rtc::WHITE); }
    }
  }
}
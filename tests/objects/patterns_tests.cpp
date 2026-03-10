#include <RayTracerChallenge/objects/patterns.hpp>
#include <RayTracerChallenge/objects/sphere.hpp>
#include <catch2/catch_test_macros.hpp>

SCENARIO("A stripe pattern is constant in y") {
  GIVEN("pattern = stripePatter(white, black)") {
    const auto pattern = rtc::StripePattern{rtc::WHITE, rtc::BLACK};
    THEN("pattern.stripeAt(point(0, 0, 0)) = white")
    AND_THEN("pattern.stripeAt(point(0, 1, 0)) = white")
    AND_THEN("pattern.stripeAt(point(0, 2, 0)) = white") {
      CHECK(pattern.patternAt(rtc::point(0, 0, 0)) == rtc::WHITE);
      CHECK(pattern.patternAt(rtc::point(0, 1, 0)) == rtc::WHITE);
      CHECK(pattern.patternAt(rtc::point(0, 2, 0)) == rtc::WHITE);
    }
  }
}

SCENARIO("A stripe pattern is constant in z") {
  GIVEN("pattern = stripePatter(white, black)") {
    const auto pattern = rtc::StripePattern{rtc::WHITE, rtc::BLACK};
    THEN("pattern.stripeAt(point(0, 0, 0)) = white")
    AND_THEN("pattern.stripeAt(point(0, 0, 1)) = white")
    AND_THEN("pattern.stripeAt(point(0, 0, 2)) = white") {
      CHECK(pattern.patternAt(rtc::point(0, 0, 0)) == rtc::WHITE);
      CHECK(pattern.patternAt(rtc::point(0, 0, 1)) == rtc::WHITE);
      CHECK(pattern.patternAt(rtc::point(0, 0, 2)) == rtc::WHITE);
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
      CHECK(pattern.patternAt(rtc::point(0, 0, 0)) == rtc::WHITE);
      CHECK(pattern.patternAt(rtc::point(0.9, 0, 0)) == rtc::WHITE);
      CHECK(pattern.patternAt(rtc::point(1, 0, 0)) == rtc::BLACK);
      CHECK(pattern.patternAt(rtc::point(-1, 0, 0)) == rtc::BLACK);
      CHECK(pattern.patternAt(rtc::point(-1.1, 0, 0)) == rtc::WHITE);
      CHECK(pattern.patternAt(rtc::point(-0.1, 0, 0)) == rtc::BLACK);
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
      const auto c = pattern.patternAtObject(&object, rtc::point(1.5, 0, 0));
      THEN("c = white") { CHECK(c == rtc::WHITE); }
    }
  }
}

SCENARIO("A gradient linearly interpolates between colours.") {
  GIVEN("p = gradientPattern(white, black)") {
    const auto p = rtc::GradientPattern{rtc::WHITE, rtc::BLACK};
    THEN("p.patternAt(point(0, 0, 0)) = white")
    AND_THEN("p.patternAt(point(0.25, 0, 0)) = colour(0.75, 0.75, 0.75)")
    AND_THEN("p.patternAt(point(0.5, 0, 0)) = colour(0.5, 0.5, 0.5)")
    AND_THEN("p.patternAt(point(0.75, 0, 0)) = colour(0.25, 0.25, 0.25)") {
      CHECK(p.patternAt(rtc::point(0, 0, 0)) == rtc::WHITE);
      CHECK(p.patternAt(rtc::point(0.25, 0, 0)) ==
            rtc::Colour{0.75f, 0.75f, 0.75f});
      CHECK(p.patternAt(rtc::point(0.5, 0, 0)) ==
            rtc::Colour{0.5f, 0.5f, 0.5f});
      CHECK(p.patternAt(rtc::point(0.75, 0, 0)) ==
            rtc::Colour{0.25f, 0.25f, 0.25f});
    }
  }
}

SCENARIO("A ring should extend in both x and z.") {
  GIVEN("pattern = ringPattern(white, black)") {
    const auto pattern = rtc::RingPattern{rtc::WHITE, rtc::BLACK};
    THEN("p.patternAt(point(0, 0, 0)) = white")
    AND_THEN("p.patternAt(point(1, 0, 0)) = black")
    AND_THEN("p.patternAt(point(0, 0, 1)) = black")
    AND_THEN("p.patternAt(point(0.708, 0, 0.708)) = black") {
      CHECK(pattern.patternAt(rtc::point(0, 0, 0)) == rtc::WHITE);
      CHECK(pattern.patternAt(rtc::point(1, 0, 0)) == rtc::BLACK);
      CHECK(pattern.patternAt(rtc::point(0, 0, 1)) == rtc::BLACK);
      CHECK(pattern.patternAt(rtc::point(0.708, 0, 0.708)) == rtc::BLACK);
    }
  }
}

SCENARIO("Checker patterns repeat in the x dimensions.") {
  GIVEN("pattern = checkerPattern(white, black)") {
    const auto pattern = rtc::CheckerPattern{rtc::WHITE, rtc::BLACK};
    THEN("p.patternAt(point(0, 0, 0)) = white")
    AND_THEN("p.patternAt(point(0.99, 0, 0)) = white")
    AND_THEN("p.patternAt(point(1.01, 0, 0)) = black") {
      CHECK(pattern.patternAt(rtc::point(0, 0, 0)) == rtc::WHITE);
      CHECK(pattern.patternAt(rtc::point(0.99, 0, 0)) == rtc::WHITE);
      CHECK(pattern.patternAt(rtc::point(1.01, 0, 0)) == rtc::BLACK);
    }
  }
}

SCENARIO("Checker patterns repeat in the y dimensions.") {
  GIVEN("pattern = checkerPattern(white, black)") {
    const auto pattern = rtc::CheckerPattern{rtc::WHITE, rtc::BLACK};
    THEN("p.patternAt(point(0, 0, 0)) = white")
    AND_THEN("p.patternAt(point(0, 0.99, 0)) = white")
    AND_THEN("p.patternAt(point(0, 1.01, 0)) = black") {
      CHECK(pattern.patternAt(rtc::point(0, 0, 0)) == rtc::WHITE);
      CHECK(pattern.patternAt(rtc::point(0, 0.99, 0)) == rtc::WHITE);
      CHECK(pattern.patternAt(rtc::point(0, 1.01, 0)) == rtc::BLACK);
    }
  }
}

SCENARIO("Checker patterns repeat in the z dimensions.") {
  GIVEN("pattern = checkerPattern(white, black)") {
    const auto pattern = rtc::CheckerPattern{rtc::WHITE, rtc::BLACK};
    THEN("p.patternAt(point(0, 0, 0)) = white")
    AND_THEN("p.patternAt(point(0, 0, 0.99)) = white")
    AND_THEN("p.patternAt(point(0, 0, 1.01)) = black") {
      CHECK(pattern.patternAt(rtc::point(0, 0, 0)) == rtc::WHITE);
      CHECK(pattern.patternAt(rtc::point(0, 0, 0.99)) == rtc::WHITE);
      CHECK(pattern.patternAt(rtc::point(0, 0, 1.01)) == rtc::BLACK);
    }
  }
}

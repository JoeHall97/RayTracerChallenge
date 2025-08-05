#include <RayTracerChallenge/objects/camera.hpp>
#include <catch2/catch_test_macros.hpp>
#include <numbers>

SCENARIO("The pixel size for a horizontal canvas.") {
  GIVEN("c = camera(200, 125, pi/2)") {
    const rtc::Camera c{200, 125, std::numbers::pi / 2};
    THEN("c.pixelSize = 0.01") {
      REQUIRE(rtc::areFloatsEqual(c.getPixelSize(), 0.01f));
    }
  }
}

SCENARIO("The pixel size for a vertical canvas.") {
  GIVEN("c = camera(125, 200, pi/2)") {
    const rtc::Camera c{125, 200, std::numbers::pi / 2};
    THEN("c.pixelSize = 0.01") {
      REQUIRE(rtc::areFloatsEqual(c.getPixelSize(), 0.01f));
    }
  }
}

SCENARIO("Constructing a ray through the center of the canvas.") {
  GIVEN("c = camera(201, 101, pi/2)")
  AND_GIVEN("r = c.rayForPixel(100, 50)") {
    const rtc::Camera c{201, 101, std::numbers::pi / 2};
    const auto r = c.getRayForPixel(100, 50);
    THEN("r.origin = point(0, 0, 0)")
    AND_THEN("r.direction = vector(0, 0, -1)") {
      REQUIRE(r.origin == rtc::point(0, 0, 0));
      REQUIRE(r.direction == rtc::vector(0, 0, -1));
    }
  }
}

SCENARIO("Constructing a ray through a corner of the canvas.") {
  GIVEN("c = camera(201, 101, pi/2)")
  AND_GIVEN("r = c.rayForPixel(0, 0)") {
    const rtc::Camera c{201, 101, std::numbers::pi / 2};
    const auto r = c.getRayForPixel(0, 0);
    THEN("r.origin = point(0, 0, 0)")
    AND_THEN("r.direction = vector(0.66519, 0.33259, -0.66851)") {
      REQUIRE(r.origin == rtc::point(0, 0, 0));
      REQUIRE(r.direction == rtc::vector(0.66519f, 0.33259f, -0.66851f));
    }
  }
}

SCENARIO("Constructing a ray when the camera is transformed.") {
  GIVEN("c = camera(201, 101, pi/2)")
  AND_GIVEN("c.transform = rotationY(pi/4) * translation(0, -2, 5)")
  AND_GIVEN("r = c.rayForPixel(100, 50)") {
    rtc::Camera c{201, 101, std::numbers::pi / 2};
    c.setTransform(rtc::rotationMatrixY(std::numbers::pi / 4) *
                   rtc::translationMatrix(0, -2, 5));
    const auto r = c.getRayForPixel(100, 50);
    THEN("r.origin = point(0, 2, -5)")
    AND_THEN("r.direction = vector(sqrt(2)/2, 0, -sqrt(2)/2)") {
      REQUIRE(r.origin == rtc::point(0, 2, -5));
      const auto x = static_cast<float>(std::sqrt(2) / 2);
      REQUIRE(r.direction == rtc::vector(x, 0, -x));
    }
  }
}

SCENARIO("Rendering a world with a camera.") {
  GIVEN("w = defaultWorld()")
  AND_GIVEN("c = camera(11, 11, pi/2)")
  AND_GIVEN("from = point(0, 0, -5)")
  AND_GIVEN("to = point(0, 0, 0)")
  AND_GIVEN("up = vector(0, 1, 0)")
  AND_GIVEN("c.transform = viewTransform(from, to, up)") {
    const auto w = rtc::defaultWorld();
    rtc::Camera c{11, 11, std::numbers::pi / 2};
    const auto from = rtc::point(0, 0, -5);
    const auto to = rtc::point(0, 0, 0);
    const auto up = rtc::vector(0, 1, 0);
    c.setTransform(rtc::viewTransform(from, to, up));
    WHEN("image = c.render(w)") {
      const auto image = c.render(w);
      THEN("image.pixelAt(5, 5) = colour(0.38066, 0.47583, 0.2855)") {
        REQUIRE(image.getPixel(5, 5) ==
                rtc::Colour{0.38066f, 0.47583f, 0.2855f});
      }
    }
  }
}
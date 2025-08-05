#include <RayTracerChallenge/datastructures/vec4.hpp>
#include <RayTracerChallenge/objects/material.hpp>
#include <catch2/catch_test_macros.hpp>

SCENARIO("Lighting with the eye between the light and the surface.") {
  GIVEN("m = material()")
  AND_GIVEN("position = point(0, 0, 0)")
  AND_GIVEN("eyeVec = vector(0, 0, -1)")
  AND_GIVEN("normalVec = vector(0, 0, -1)")
  AND_GIVEN("light = pointLight(point(0, 0, -10), colour(1, 1, 1))") {
    const auto m = rtc::defaultMaterial();
    const auto position = rtc::point(0, 0, 0);
    const auto eyeVec = rtc::vector(0, 0, -1);
    const auto normalVec = rtc::vector(0, 0, -1);
    const rtc::Light light{rtc::Colour(1, 1, 1), rtc::point(0, 0, -10)};
    WHEN("result = m.lighting(light, position, eyeVec, normalVec)") {
      const auto result = m.lighting(light, position, eyeVec, normalVec);
      THEN("result = colour(1.9, 1.9, 1.9)") {
        REQUIRE(result == rtc::Colour{1.9f, 1.9f, 1.9f});
      }
    }
  }
}

SCENARIO("Lighting with the eye between the light and the surface, at a 45 "
         "degree offset.") {
  GIVEN("m = material()")
  AND_GIVEN("position = point(0, 0, 0)")
  AND_GIVEN("eyeVec = vector(0, sqrt(2)/2, -sqrt(2)/2)")
  AND_GIVEN("normalVec = vector(0, 0, -1)")
  AND_GIVEN("light = pointLight(point(0, 0, -10), colour(1, 1, 1))") {
    const auto m = rtc::defaultMaterial();
    const auto position = rtc::point(0, 0, 0);
    const auto y = static_cast<float>(sqrt(2) / 2);
    const auto eyeVec = rtc::vector(0, y, -y);
    const auto normalVec = rtc::vector(0, 0, -1);
    const rtc::Light light{rtc::Colour(1, 1, 1), rtc::point(0, 0, -10)};
    WHEN("result = m.lighting(light, position, eyeVec, normalVec)") {
      const auto result = m.lighting(light, position, eyeVec, normalVec);
      THEN("result = colour(1, 1, 1)") {
        REQUIRE(result == rtc::Colour{1, 1, 1});
      }
    }
  }
}

SCENARIO("Lighting with eye opposite surface, light offset 45 degrees.") {
  GIVEN("m = material()")
  AND_GIVEN("position = point(0, 0, 0)")
  AND_GIVEN("eyeVec = vector(0, 0, -1)")
  AND_GIVEN("normalVec = vector(0, 0, -1)")
  AND_GIVEN("light = pointLight(point(0, 10, -10), colour(1, 1, 1))") {
    const auto m = rtc::defaultMaterial();
    const auto position = rtc::point(0, 0, 0);
    const auto eyeVec = rtc::vector(0, 0, -1);
    const auto normalVec = rtc::vector(0, 0, -1);
    const rtc::Light light{rtc::Colour(1, 1, 1), rtc::point(0, 10, -10)};
    WHEN("result = m.lighting(light, position, eyeVec, normalVec)") {
      const auto result = m.lighting(light, position, eyeVec, normalVec);
      THEN("result = colour(0.7364, 0.7364, 0.7364)") {
        REQUIRE(result == rtc::Colour{0.7364f, 0.7364f, 0.7364f});
      }
    }
  }
}

SCENARIO("Lighting with an eye in the path of the reflection vector.") {
  GIVEN("m = material()")
  AND_GIVEN("position = point(0, 0, 0)")
  AND_GIVEN("eyeVec = vector(0, -sqrt(2)/2, -sqrt(2)/2)")
  AND_GIVEN("normalVec = vector(0, 0, -1)")
  AND_GIVEN("light = pointLight(point(0, 10, -10), colour(1, 1, 1))") {
    const auto m = rtc::defaultMaterial();
    const auto position = rtc::point(0, 0, 0);
    const auto y = static_cast<float>(sqrt(2) / 2);
    const auto eyeVec = rtc::vector(0, -y, -y);
    const auto normalVec = rtc::vector(0, 0, -1);
    const rtc::Light light{rtc::Colour(1, 1, 1), rtc::point(0, 10, -10)};
    WHEN("result = m.lighting(light, position, eyeVec, normalVec)") {
      const auto result = m.lighting(light, position, eyeVec, normalVec);
      THEN("result = colour(1.6364, 1.6364, 1.6364)") {
        REQUIRE(result == rtc::Colour{1.63639f, 1.63639f, 1.63639f});
      }
    }
  }
}

SCENARIO("Lighting with the light behind the surface.") {
  GIVEN("m = material()")
  AND_GIVEN("position = point(0, 0, 0)")
  AND_GIVEN("eyeVec = vector(0, 0, -1)")
  AND_GIVEN("normalVec = vector(0, 0, -1)")
  AND_GIVEN("light = pointLight(point(0, 0, 10), colour(1, 1, 1))") {
    const auto m = rtc::defaultMaterial();
    const auto position = rtc::point(0, 0, 0);
    const auto eyeVec = rtc::vector(0, 0, -1);
    const auto normalVec = rtc::vector(0, 0, -1);
    const rtc::Light light{rtc::Colour(1, 1, 1), rtc::point(0, 0, 10)};
    WHEN("result = m.lighting(light, position, eyeVec, normalVec)") {
      const auto result = m.lighting(light, position, eyeVec, normalVec);
      THEN("result = colour(0.1, 0.1, 0.1)") {
        REQUIRE(result == rtc::Colour{0.1f, 0.1f, 0.1f});
      }
    }
  }
}

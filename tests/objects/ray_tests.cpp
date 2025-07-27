#include <RayTracerChallenge/datastructures/vec4.hpp>
#include <RayTracerChallenge/objects/ray.hpp>
#include <RayTracerChallenge/objects/sphere.hpp>
#include <catch2/catch_test_macros.hpp>

using rtc::Ray, rtc::point, rtc::vector;

SCENARIO("Creating and querying a Ray.") {
  GIVEN("origin = point(1, 2, 3)")
  AND_GIVEN("direction = vector(4, 5, 6)") {
    const auto origin = point(1, 2, 3);
    const auto direction = vector(4, 5, 6);
    WHEN("r = Ray(origin, direction)") {
      const auto r = Ray{origin, direction};
      THEN("r.origin = origin")
      AND_THEN("r.direction = direction") {
        CHECK(r.origin == origin);
        CHECK(r.direction == direction);
      }
    }
  }
}

SCENARIO("Computing a point from a distance.") {
  GIVEN("r = Ray(point(2, 3, 4), vector(1, 0, 0))") {
    const Ray r{point(2, 3, 4), vector(1, 0, 0)};
    THEN("r.position(0) == point(2, 3, 4)")
    AND_THEN("r.position(1) == point(3, 3, 4)")
    AND_THEN("r.position(-1) == point(1, 3, 4)")
    AND_THEN("r.position(4.5) == point(6.5, 3, 4)") {
      CHECK(r.position(0) == point(2, 3, 4));
      CHECK(r.position(1) == point(3, 3, 4));
      CHECK(r.position(-1) == point(1, 3, 4));
      CHECK(r.position(4.5) == point(6.5, 3, 4));
    }
  }
}

SCENARIO("Translating a ray.") {
  GIVEN("r = Ray(point(1, 2, 3), vector(0, 1, 0))")
  AND_GIVEN("m = translation(3, 4, 5)") {
    const Ray r{point(1, 2, 3), vector(0, 1, 0)};
    const auto m = rtc::translationMatrix(3, 4, 5);
    WHEN("r2 = r.transform(m)") {
      const auto r2 = r.transform(m);
      THEN("r2.origin = point(4, 6, 8)")
      AND_THEN("r2.direction = vector(0, 1, 0)") {
        CHECK(r2.origin == point(4, 6, 8));
        CHECK(r2.direction == vector(0, 1, 0));
      }
    }
  }
}

SCENARIO("Scaling a ray.") {
  GIVEN("r = Ray(point(1, 2, 3), vector(0, 1, 0))")
  AND_GIVEN("m = translation(2, 3, 4)") {
    const Ray r{point(1, 2, 3), vector(0, 1, 0)};
    const auto m = rtc::scalingMatrix(2, 3, 4);
    WHEN("r2 = r.transform(m)") {
      const auto r2 = r.transform(m);
      THEN("r2.origin = point(2, 6, 12)")
      AND_THEN("r2.direction = vector(0, 3, 0)") {
        CHECK(r2.origin == point(2, 6, 12));
        CHECK(r2.direction == vector(0, 3, 0));
      }
    }
  }
}

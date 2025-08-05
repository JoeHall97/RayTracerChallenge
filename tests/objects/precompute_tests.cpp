#include <RayTracerChallenge/objects/precompute.hpp>
#include <RayTracerChallenge/objects/sphere.hpp>
#include <catch2/catch_test_macros.hpp>

SCENARIO("Prepare the state of an intersection.") {
  GIVEN("r = ray(point(0, 0, -5), vector(0, 0, 1))")
  AND_GIVEN("shape = sphere()")
  AND_GIVEN("i = intersection(4, shape)") {
    const auto r = rtc::Ray{rtc::point(0, 0, -5), rtc::vector(0, 0, 1)};
    const auto shape = rtc::sphere();
    const auto i = rtc::Intersection{4, &shape};
    WHEN("state = prepareComputation(i, r)") {
      const auto state = rtc::prepareComputation(i, r);
      THEN("state.t = i.t")
      AND_THEN("state.object = i.object")
      AND_THEN("state.point = point(0, 0, -1)")
      AND_THEN("state.eyeVec = vector(0, 0, -1)")
      AND_THEN("state.normalVec = vector(0, 0, -1)") {
        CHECK(state.t == i.t);
        CHECK(state.object == i.object);
        CHECK(state.point == rtc::point(0, 0, -1));
        CHECK(state.eyeVec == rtc::vector(0, 0, -1));
        CHECK(state.normalVec == rtc::vector(0, 0, -1));
      }
    }
  }
}

SCENARIO("The hit, when an intersection occurs on the outside.") {
  GIVEN("r = ray(point(0, 0, -5), vector(0, 0, 1))")
  AND_GIVEN("shape = sphere()")
  AND_GIVEN("i = intersection(4, shape)") {
    const auto r = rtc::Ray{rtc::point(0, 0, -5), rtc::vector(0, 0, 1)};
    const auto shape = rtc::sphere();
    const auto i = rtc::Intersection{4, &shape};
    WHEN("state = prepareComputation(i, r)") {
      const auto state = rtc::prepareComputation(i, r);
      THEN("state.inside = false") { CHECK(!state.inside); }
    }
  }
}

SCENARIO("The hit, when an intersection occurs on the inside.") {
  GIVEN("r = ray(point(0, 0, 0), vector(0, 0, 1))")
  AND_GIVEN("shape = sphere()")
  AND_GIVEN("i = intersection(1, shape)") {
    const auto r = rtc::Ray{rtc::point(0, 0, 0), rtc::vector(0, 0, 1)};
    const auto shape = rtc::sphere();
    const auto i = rtc::Intersection{1, &shape};
    WHEN("state = prepareComputation(i, r)") {
      const auto state = rtc::prepareComputation(i, r);
      THEN("state.inside = true") { CHECK(state.inside); }
    }
  }
}

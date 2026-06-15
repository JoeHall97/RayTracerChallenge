#include "RayTracerChallenge/datastructures/vec4.hpp"
#include "RayTracerChallenge/helpers/helpers.hpp"
#include "RayTracerChallenge/objects/patterns.hpp"
#include "catch2/generators/catch_generators.hpp"
#include <RayTracerChallenge/objects/cube.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_all.hpp>

SCENARIO("A ray intersects a cube.") {
  const auto [origin, direction, t1, t2] =
      GENERATE(table<rtc::Vec4, rtc::Vec4, float, float>(
          {// positive x
           {rtc::point(5.0f, 0.5f, 0), rtc::vector(-1.0f, 0, 0), 4.0f, 6.0f},
           // negative x
           {rtc::point(-5.0f, 0.5f, 0), rtc::vector(1.0f, 0, 0), 4.0f, 6.0f},
           // positive y
           {rtc::point(0.5f, 5.0f, 0), rtc::vector(0, -1.0f, 0), 4.0f, 6.0f},
           // negative y
           {rtc::point(0.5f, -5.0f, 0), rtc::vector(0, 1.0f, 0), 4.0f, 6.0f},
           // positive z
           {rtc::point(0.5f, 0, 5.0f), rtc::vector(0, 0, -1.0f), 4.0f, 6.0f},
           // negative z
           {rtc::point(0.5f, 0, -5.0f), rtc::vector(0, 0, 1.0f), 4.0f, 6.0f},
           // inside
           {rtc::point(0, 0.5f, 0), rtc::vector(0, 0, 1.0f), -1.0f, 1.0f}}));

  GIVEN("c = cube()")
  AND_GIVEN("r = ray(" + origin.str() + ",  " + direction.str() + ")") {
    const rtc::Cube c{};
    const rtc::Ray r{origin, direction};

    WHEN("xs = c.localIntersect(r)") {
      const auto xs = c.localIntersect(r);

      THEN("xs.count = 2")
      AND_THEN("xs[0].t = " + std::to_string(t1))
      AND_THEN("xs[1].t = " + std::to_string(t2)) {
        CHECK(xs.size() == 2);
        CHECK(rtc::areFloatsEqual(xs.begin()->t, t1));
        CHECK(rtc::areFloatsEqual(std::next(xs.begin(), 1)->t, t2));
      }
    }
  }
}
SCENARIO("A ray misses a cube.") {
  const auto [origin, direction] = GENERATE(table<rtc::Vec4, rtc::Vec4>(
      {{rtc::point(-2.0f, 0, 0), rtc::vector(0.2673f, 0.5345f, 0.8018f)},
       {rtc::point(0, -2.0f, 0), rtc::vector(0.8018f, 0.2673f, 0.5345f)},
       {rtc::point(0, 0, -2.0f), rtc::vector(0.5345f, 0.8018f, 0.2673f)},
       {rtc::point(2.0f, 0, 2.0f), rtc::vector(0, 0, -1.0f)},
       {rtc::point(0, 2.0f, 2.0f), rtc::vector(0, -1.0f, 0)},
       {rtc::point(2.0f, 2.0f, 0), rtc::vector(-1.0f, 0, 0)}}));

  GIVEN("c = cube()")
  AND_GIVEN("r = ray(" + origin.str() + ",  " + direction.str() + ")") {
    const rtc::Cube c{};
    const rtc::Ray r{origin, direction};

    WHEN("xs = c.localIntersect(r)") {
      const auto xs = c.localIntersect(r);

      THEN("xs.count = 0") { CHECK(xs.empty()); }
    }
  }
}

SCENARIO("The normal on the surface of a cube.") {
  const auto [point, expectedNormal] = GENERATE(table<rtc::Vec4, rtc::Vec4>({
      {rtc::point(1, 0.5f, -0.8f), rtc::vector(1, 0, 0)},
      {rtc::point(-1, -0.2f, 0.9f), rtc::vector(-1, 0, 0)},
      {rtc::point(-0.4f, 1, -0.1f), rtc::vector(0, 1, 0)},
      {rtc::point(0.3f, -1, -0.7f), rtc::vector(0, -1, 0)},
      {rtc::point(-0.6f, 0.3f, 1), rtc::vector(0, 0, 1)},
      {rtc::point(0.4f, 0.4f, -1), rtc::vector(0, 0, -1)},
      {rtc::point(1, 1, 1), rtc::vector(1, 0, 0)},
      {rtc::point(-1, -1, -1), rtc::vector(-1, 0, 0)},
  }));

  GIVEN("c = cube()")
  AND_GIVEN("p = " + point.str()) {
    const rtc::Cube c{};
    const auto p = point;

    WHEN("normal = c.localNormal(p)") {
      const auto normal = c.localNormalAt(p);

      THEN("normal = " + expectedNormal.str()) {
        CHECK(normal == expectedNormal);
      }
    }
  }
}

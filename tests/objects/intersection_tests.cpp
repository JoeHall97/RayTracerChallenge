#include "RayTracerChallenge/datastructures/matrix.hpp"
#include "RayTracerChallenge/datastructures/vec4.hpp"
#include "RayTracerChallenge/helpers/helpers.hpp"
#include "RayTracerChallenge/objects/material.hpp"
#include "RayTracerChallenge/objects/plane.hpp"
#include "RayTracerChallenge/objects/precompute.hpp"
#include "RayTracerChallenge/objects/world.hpp"
#include <RayTracerChallenge/objects/intersection.hpp>
#include <RayTracerChallenge/objects/sphere.hpp>
#include <catch2/catch_test_macros.hpp>

using rtc::sphere, rtc::Intersection, rtc::hit, rtc::SortedIntersections;

SCENARIO("The hit, when all intersections have t.") {
  GIVEN("s = sphere()")
  AND_GIVEN("i1 = intersection(1, s)")
  AND_GIVEN("i2 = intersection(2, s)")
  AND_GIVEN("xs = intersections(i1, i2)") {
    auto s = sphere();
    const auto i1 = Intersection{1, &s};
    const auto i2 = Intersection{2, &s};
    const SortedIntersections xs{i1, i2};
    WHEN("i = hit(xs)") {
      const auto i = hit(xs);
      THEN("i = i1") { CHECK((i.has_value() && i.value() == i1)); }
    }
  }
}

SCENARIO("The hit, when some intersection has a negative t.") {
  GIVEN("s = sphere()")
  AND_GIVEN("i1 = intersection(-1, s)")
  AND_GIVEN("i2 = intersection(2, s)")
  AND_GIVEN("xs = intersections(i1, i2)") {
    auto s = sphere();
    const auto i1 = Intersection{-1, &s};
    const auto i2 = Intersection{2, &s};
    const SortedIntersections xs{i1, i2};
    WHEN("i = hit(xs)") {
      const auto i = hit(xs);
      THEN("i = i2") { CHECK((i.has_value() && i.value() == i2)); }
    }
  }
}

SCENARIO("The hit, when all intersection hava a negative t.") {
  GIVEN("s = sphere()")
  AND_GIVEN("i1 = intersection(-1, s)")
  AND_GIVEN("i2 = intersection(-2, s)")
  AND_GIVEN("xs = intersections(i1, i2)") {
    auto s = sphere();
    const auto i1 = Intersection{-1, &s};
    const auto i2 = Intersection{-2, &s};
    const SortedIntersections xs{i1, i2};
    WHEN("i = hit(xs)") {
      const auto i = hit(xs);
      THEN("i = nothing") { CHECK(!i.has_value()); }
    }
  }
}

SCENARIO("The hit, is always the lowest non-negative t.") {
  GIVEN("s = sphere()")
  AND_GIVEN("i1 = intersection(7, s)")
  AND_GIVEN("i2 = intersection(5, s)")
  AND_GIVEN("i3 = intersection(-3, s)")
  AND_GIVEN("i4 = intersection(2, s)")
  AND_GIVEN("xs = intersections(i1, i2, i3, i4)") {
    auto s = sphere();
    const auto i1 = Intersection{7, &s};
    const auto i2 = Intersection{5, &s};
    const auto i3 = Intersection{-3, &s};
    const auto i4 = Intersection{2, &s};
    const SortedIntersections xs{i1, i2, i3, i4};
    WHEN("i = hit(xs)") {
      const auto i = hit(xs);
      THEN("i = nothing") { CHECK((i.has_value() && i.value() == i4)); }
    }
  }
}

SCENARIO("The Schlick approximation under total internal refraction.") {
  GIVEN("shape = glassSphere()")
  AND_GIVEN("r = ray(point(0,0,sqrt(2)/2), vector(0,1,0))")
  AND_GIVEN("xs = intersections(-sqrt(2)/2:shape, sqrt(2)/2:shape)") {
    const auto shape = rtc::glassSphere();
    const rtc::Ray r{rtc::point(0, 0, std::sqrt(2.0f) / 2),
                     rtc::vector(0, 1, 0)};
    const rtc::SortedIntersections xs{
        rtc::Intersection{-std::sqrt(2.0f) / 2.0f, &shape},
        rtc::Intersection{std::sqrt(2.0f) / 2, &shape}};

    WHEN("comps = prepareComputations(xs[1], r, xs)")
    AND_WHEN("reflectance = comps.schlick()") {
      const auto comps =
          rtc::prepareComputation(*std::next(xs.begin(), 1), r, xs);
      const auto reflectance = comps.schlick();

      THEN("reflectance = 1.0") { CHECK(reflectance == 1.0f); }
    }
  }
}

SCENARIO("The Schlick approximation with a perpendicular viewing angle.") {
  GIVEN("shape = glassSphere()")
  AND_GIVEN("r = ray(point(0,0,0), vector(0,1,0))")
  AND_GIVEN("xs = intersections(-1:shape, 1:shape)") {
    const auto shape = rtc::glassSphere();
    const rtc::Ray r{rtc::point(0, 0, 0), rtc::vector(0, 1, 0)};
    const rtc::SortedIntersections xs{rtc::Intersection{-1.0f, &shape},
                                      rtc::Intersection{1.0f, &shape}};

    WHEN("comps = prepareComputations(xs[1], r, xs)")
    AND_WHEN("reflectance = comps.schlick()") {
      const auto comps =
          rtc::prepareComputation(*std::next(xs.begin(), 1), r, xs);
      const auto reflectance = comps.schlick();

      THEN("reflectance = 0.04") {
        CHECK(rtc::areFloatsEqual(reflectance, 0.04f));
      }
    }
  }
}

SCENARIO("Schlick approximation with a small angle and n2 > n1") {
  GIVEN("shape = glassSphere()")
  AND_GIVEN("r = ray(point(0,0.99,-2), vector(0,0,1))")
  AND_GIVEN("xs = intersections(1.8589:shape)") {
    const auto shape = rtc::glassSphere();
    const rtc::Ray r{rtc::point(0, 0.99f, -2.0f), rtc::vector(0, 0, 1.0f)};
    const rtc::SortedIntersections xs{rtc::Intersection{1.8589f, &shape}};

    WHEN("comps = prepareComputation(xs[0], r, xs)")
    AND_WHEN("reflectance = comps.schlick()") {
      const auto comps = rtc::prepareComputation(*xs.begin(), r, xs);
      const auto reflectance = comps.schlick();

      THEN("reflectance = 0.48873") {
        CHECK(rtc::areFloatsEqual(reflectance, 0.48873f));
      }
    }
  }
}

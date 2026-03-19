#include "RayTracerChallenge/datastructures/vec4.hpp"
#include "RayTracerChallenge/objects/intersection.hpp"
#include "RayTracerChallenge/objects/plane.hpp"
#include <RayTracerChallenge/objects/precompute.hpp>
#include <RayTracerChallenge/objects/sphere.hpp>
#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include <iterator>

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

SCENARIO("Precomputing the reflection vector.") {
  GIVEN("shape = plane()")
  AND_GIVEN("r = ray(point(0,1,-1), vector(0,-sqrt(2)/2),sqrt(2)/2))")
  AND_GIVEN("i = intersection(sqrt(2), shape)") {
    const auto shape = rtc::plane();
    const auto r =
        rtc::Ray{rtc::point(0, 1, -1),
                 rtc::vector(0, -std::sqrt(2.0f) / 2, std::sqrt(2.0f) / 2)};
    const auto i = rtc::Intersection{std::sqrt(2.0f), &shape};
    WHEN("state = prepareComputation(i, r)") {
      const auto state = rtc::prepareComputation(i, r);
      THEN("state.reflectVec = vector(0,sqrt(2)/2),sqrt(2)/2))") {
        CHECK(state.reflectVec ==
              rtc::vector(0, std::sqrt(2.0f) / 2, std::sqrt(2.0f) / 2));
      }
    }
  }
}

SCENARIO("Finding n1 and n2 at various intersections.") {
  GIVEN("a = glassSphere()")
  AND_GIVEN("a.transform = scaling(2,2,2)")
  AND_GIVEN("a.material.refractiveIndex = 1.5")
  AND_GIVEN("b = glassSphere()")
  AND_GIVEN("b.transform = translation(0,0,-0.25)")
  AND_GIVEN("b.material.refractiveIndex = 2.0")
  AND_GIVEN("c = glassSphere()")
  AND_GIVEN("c.transform = translation(0,0,0.25)")
  AND_GIVEN("c.material.refractiveIndex = 2.5")
  AND_GIVEN("r = ray(point(0,0,-4),vector(0,0,1))")
  AND_GIVEN("xs ← intersections(2:A, 2.75:B, 3.25:C, 4.75:B, 5.25:C, 6:A)") {
    auto a = rtc::glassSphere();
    a.setTransformationMatrix(rtc::scalingMatrix(2, 2, 2));
    auto aMaterial = a.getMaterial();
    aMaterial.refractiveIndex = 1.5;
    a.setMaterial(aMaterial);

    auto b = rtc::glassSphere();
    b.setTransformationMatrix(rtc::translationMatrix(0, 0, -0.25));
    auto bMaterial = b.getMaterial();
    bMaterial.refractiveIndex = 2;
    b.setMaterial(bMaterial);

    auto c = rtc::glassSphere();
    c.setTransformationMatrix(rtc::translationMatrix(0, 0, 0.25));
    auto cMaterial = c.getMaterial();
    cMaterial.refractiveIndex = 2.5;
    c.setMaterial(cMaterial);

    const rtc::Ray r{rtc::point(0, 0, -4), rtc::vector(0, 0, -1)};
    const rtc::SortedIntersections xs{
        rtc::Intersection{2, &a},    rtc::Intersection{2.75, &b},
        rtc::Intersection{3.25, &c}, rtc::Intersection{4.75, &b},
        rtc::Intersection{5.25, &c}, rtc::Intersection{6, &a}};

    WHEN("comps = prepareComputations(xs[0], r, xs)") {
      const auto i = *xs.begin();
      const auto comps = rtc::prepareComputation(i, r, xs);
      THEN("comps.n1 = 1.0")
      AND_THEN("comps.n2 = 1.5") {
        CHECK(rtc::areFloatsEqual(comps.n1, 1.0f));
        CHECK(rtc::areFloatsEqual(comps.n2, 1.5f));
      }
    }

    WHEN("comps = prepareComputations(xs[1], r, xs)") {
      const auto i = *std::next(xs.begin(), 1);
      const auto comps = rtc::prepareComputation(i, r, xs);
      THEN("comps.n1 = 1.5")
      AND_THEN("comps.n2 = 2.0") {
        CHECK(rtc::areFloatsEqual(comps.n1, 1.5f));
        CHECK(rtc::areFloatsEqual(comps.n2, 2.0f));
      }
    }

    WHEN("comps = prepareComputations(xs[2], r, xs)") {
      const auto i = *std::next(xs.begin(), 2);
      const auto comps = rtc::prepareComputation(i, r, xs);
      THEN("comps.n1 = 2.0")
      AND_THEN("comps.n2 = 2.5") {
        CHECK(rtc::areFloatsEqual(comps.n1, 2.0f));
        CHECK(rtc::areFloatsEqual(comps.n2, 2.5f));
      }
    }

    WHEN("comps = prepareComputations(xs[3], r, xs)") {
      const auto i = *std::next(xs.begin(), 3);
      const auto comps = rtc::prepareComputation(i, r, xs);
      THEN("comps.n1 = 2.5")
      AND_THEN("comps.n2 = 2.5") {
        CHECK(rtc::areFloatsEqual(comps.n1, 2.5f));
        CHECK(rtc::areFloatsEqual(comps.n2, 2.5f));
      }
    }

    WHEN("comps = prepareComputations(xs[4], r, xs)") {
      const auto i = *std::next(xs.begin(), 4);
      const auto comps = rtc::prepareComputation(i, r, xs);
      THEN("comps.n1 = 2.5")
      AND_THEN("comps.n2 = 1.5") {
        CHECK(rtc::areFloatsEqual(comps.n1, 2.5f));
        CHECK(rtc::areFloatsEqual(comps.n2, 1.5f));
      }
    }

    WHEN("comps = prepareComputations(xs[5], r, xs)") {
      const auto i = *std::next(xs.begin(), 5);
      const auto comps = rtc::prepareComputation(i, r, xs);
      THEN("comps.n1 = 1.5")
      AND_THEN("comps.n2 = 1.0") {
        CHECK(rtc::areFloatsEqual(comps.n1, 1.5f));
        CHECK(rtc::areFloatsEqual(comps.n2, 1.0f));
      }
    }
  }
}

#include <RayTracerChallenge/objects/plane.hpp>
#include <catch2/catch_test_macros.hpp>

SCENARIO("The normal of a plane is constant everywhere") {
  GIVEN("p = plane()") {
    const auto p = rtc::plane();
    WHEN("n1 = p.localNormalAt(point(0, 0, 0))")
    AND_WHEN("n2 = p.localNormalAt(point(10, 0, -10))")
    AND_WHEN("n3 = p.localNormalAt(point(-5, 0, 150))") {
      const auto n1 = p.localNormalAt(rtc::point(0, 0, 0));
      const auto n2 = p.localNormalAt(rtc::point(10, 0, -10));
      const auto n3 = p.localNormalAt(rtc::point(-5, 0, 150));
      THEN("n1 = vector(0, 1, 0)")
      AND_THEN("n2 = vector(0, 1, 0)")
      AND_THEN("n3 = vector(0, 1, 0)") {
        CHECK(n1 == rtc::vector(0, 1, 0));
        CHECK(n2 == rtc::vector(0, 1, 0));
        CHECK(n3 == rtc::vector(0, 1, 0));
      }
    }
  }
}

SCENARIO("Intersect with a ray parallel to the plane") {
  GIVEN("p = plane()")
  AND_GIVEN("r = ray(point(0, 10, 0), vector(0, 0, 1))") {
    const auto p = rtc::plane();
    const auto r = rtc::Ray(rtc::point(0, 10, 0), rtc::vector(0, 0, 1));
    WHEN("xs = p.localIntersect(r)") {
      const auto xs = p.localIntersect(r);
      THEN("xs is empty") { CHECK(xs.empty()); }
    }
  }
}

SCENARIO("Intersect with a coplanar ray") {
  GIVEN("p = plane()")
  AND_GIVEN("r = ray(point(0, 0, 0), vector(0, 0, 1))") {
    const auto p = rtc::plane();
    const auto r = rtc::Ray(rtc::point(0, 0, 0), rtc::vector(0, 0, 1));
    WHEN("xs = p.localIntersect(r)") {
      const auto xs = p.localIntersect(r);
      THEN("xs is empty") { CHECK(xs.empty()); }
    }
  }
}

SCENARIO("A ray intersecting a plane from above.") {
  GIVEN("p = plane()")
  AND_GIVEN("r = ray(point(0, 1, 0), vector(0, -1, 0))") {
    const auto p = rtc::plane();
    const auto r = rtc::Ray(rtc::point(0, 1, 0), rtc::vector(0, -1, 0));
    WHEN("xs = p.localIntersect(r)") {
      const auto xs = p.localIntersect(r);
      THEN("xs.count = 1")
      AND_THEN("xs[0].t = 1")
      AND_THEN("xs[0].object = p") {
        CHECK(xs.size() == 1);
        CHECK(xs.begin()->t == 1);
        CHECK(xs.begin()->object == &p);
      }
    }
  }
}

SCENARIO("A ray intersecting a plane from below.") {
  GIVEN("p = plane()")
  AND_GIVEN("r = ray(point(0, -1, 0), vector(0, 1, 0))") {
    const auto p = rtc::plane();
    const auto r = rtc::Ray(rtc::point(0, -1, 0), rtc::vector(0, 1, 0));
    WHEN("xs = p.localIntersect(r)") {
      const auto xs = p.localIntersect(r);
      THEN("xs.count = 1")
      AND_THEN("xs[0].t = 1")
      AND_THEN("xs[0].object = p") {
        CHECK(xs.size() == 1);
        CHECK(xs.begin()->t == 1);
        CHECK(xs.begin()->object == &p);
      }
    }
  }
}
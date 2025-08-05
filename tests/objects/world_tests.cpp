#include <RayTracerChallenge/objects/ray.hpp>
#include <RayTracerChallenge/objects/world.hpp>
#include <catch2/catch_test_macros.hpp>

SCENARIO("Intersect a world with a ray.") {
  GIVEN("w = defaultWorld()")
  AND_GIVEN("r = ray(point(0, 0, -5), vector(0, 0, 1))") {
    const auto w = rtc::defaultWorld();
    const rtc::Ray r{rtc::point(0, 0, -5), rtc::vector(0, 0, 1)};
    WHEN("xs = w.intersect(r)") {
      const auto xs = w.intersections(r);
      THEN("xs.count = 4")
      AND_THEN("xs[0].t = 4")
      AND_THEN("xs[1].t = 4.5")
      AND_THEN("xs[2].t = 5.5")
      AND_THEN("xs[3].t = 6") {
        REQUIRE(xs.size() == 4);
        auto it = xs.begin();
        CHECK(it->t == 4);
        ++it;
        CHECK(it->t == 4.5);
        ++it;
        CHECK(it->t == 5.5);
        ++it;
        CHECK(it->t == 6);
      }
    }
  }
}

SCENARIO("Shading an intersection.") {
  GIVEN("w = defaultWorld()")
  AND_GIVEN("r = ray(point(0, 0, -5), vector(0, 0, 1))") {
    const auto w = rtc::defaultWorld();
    const rtc::Ray r{rtc::point(0, 0, -5), rtc::vector(0, 0, 1)};
    WHEN("c = w.colourAt(r)") {
      const auto c = w.colourAt(r);
      THEN("c = colour(0.38066, 0.47583, 0.2855)") {
        CHECK(c == rtc::Colour{0.38066f, 0.47583f, 0.2855f});
      }
    }
  }
}

SCENARIO("Shading an intersection from the side.") {
  GIVEN("w = defaultWorld()")
  AND_GIVEN("w.light = pointLight(point(0, 0.25, 0), colour(1, 1, 1))")
  AND_GIVEN("r = ray(point(0, 0, 0), vector(0, 0, 1))") {
    auto w = rtc::defaultWorld();
    w.light = rtc::Light{rtc::Colour{1, 1, 1}, rtc::point(0, 0.25f, 0)};
    const rtc::Ray r{rtc::point(0, 0, 0), rtc::vector(0, 0, 1)};
    WHEN("c = w.colourAt(r)") {
      const auto c = w.colourAt(r);
      THEN("c = colour(0.90498, 0.90498, 0.90498)") {
        CHECK(c == rtc::Colour{0.90498f, 0.90498f, 0.90498f});
      }
    }
  }
}

SCENARIO("The colour when a ray misses.") {
  GIVEN("w = defaultWorld()")
  AND_GIVEN("r = ray(point(0, 0, -5), vector(0, 1, 0))") {
    const auto w = rtc::defaultWorld();
    const rtc::Ray r{rtc::point(0, 0, -5), rtc::vector(0, 1, 0)};
    WHEN("c = w.colourAt(r)") {
      const auto c = w.colourAt(r);
      THEN("c = colour(0, 0, 0)") { CHECK(c == rtc::Colour{0, 0, 0}); }
    }
  }
}

SCENARIO("The colour with an intersection behind the ray.") {
  GIVEN("w = defaultWorld()")
  AND_GIVEN("outer = the first object in w")
  AND_GIVEN("outer.material.ambient = 1")
  AND_GIVEN("inner = the second object in w")
  AND_GIVEN("inner.material.ambient = 1")
  AND_GIVEN("r = ray(point(0, 0, 0.75), vector(0, 0, -1))") {
    const auto w = rtc::defaultWorld();
    w.objects[0]->material.ambient = 1;
    w.objects[1]->material.ambient = 1;
    const rtc::Ray r{rtc::point(0, 0, 0.75), rtc::vector(0, 0, -1)};
    WHEN("c = w.colourAt(r)") {
      const auto c = w.colourAt(r);
      THEN("c = inner.material.colour") {
        CHECK(c == w.objects[1]->material.colour);
      }
    }
  }
}

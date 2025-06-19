#include <catch2/catch_test_macros.hpp>

#include "coord_tuple.hpp"
#include "ray.hpp"
#include "sphere.hpp"

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

SCENARIO("A Ray intersects a sphere at two points.") {
    GIVEN("r = Ray(point(0, 0, -5), vector(0, 0, 1))")
    AND_GIVEN("s = sphere()") {
        const Ray r{point(0, 0, -5), vector(0, 0, 1)};
        auto s = rtc::sphere();
        WHEN("xs = r.intersect(s)") {
            const auto xs = r.intersect(s);
            THEN("xs.count = 2")
            AND_THEN("xs[0] = 4.0")
            AND_THEN("xs[1] = 6.0") {
                CHECK(xs.size() == 2);
                CHECK(xs[0].t == 4.0);
                CHECK(xs[1].t == 6.0);
            }
        }
    }
}

SCENARIO("A Ray intersects a sphere at a tangent.") {
    GIVEN("r = Ray(point(0, 1, -5), vector(0, 0, 1))")
    AND_GIVEN("s = sphere()") {
        const Ray r{point(0, 1, -5), vector(0, 0, 1)};
        auto s = rtc::sphere();
        WHEN("xs = r.intersect(s)") {
            const auto xs = r.intersect(s);
            THEN("xs.count = 2")
            AND_THEN("xs[0] = 5.0")
            AND_THEN("xs[1] = 5.0") {
                CHECK(xs.size() == 2);
                CHECK(xs[0].t == 5.0);
                CHECK(xs[1].t == 5.0);
            }
        }
    }
}

SCENARIO("A Ray that misses a sphere.") {
    GIVEN("r = Ray(point(0, 2, -5), vector(0, 0, 1))")
    AND_GIVEN("s = sphere()") {
        const Ray r{point(0, 2, -5), vector(0, 0, 1)};
        auto s = rtc::sphere();
        WHEN("xs = r.intersect(s)") {
            const auto xs = r.intersect(s);
            THEN("xs.count = 0") {
                CHECK(xs.empty());
            }
        }
    }
}

SCENARIO("A Ray originates inside a sphere.") {
    GIVEN("r = Ray(point(0, 0, 0), vector(0, 0, 1))")
    AND_GIVEN("s = sphere()") {
        const Ray r{point(0, 0, 0), vector(0, 0, 1)};
        auto s = rtc::sphere();
        WHEN("xs = r.intersect(s)") {
            const auto xs = r.intersect(s);
            THEN("xs.count = 2")
            AND_THEN("xs[0] = -1.0")
            AND_THEN("xs[1] = 1.0") {
                CHECK(xs.size() == 2);
                CHECK(rtc::areFloatsEqual(xs[0].t, -1.0));
                CHECK(xs[1].t == 1.0);
            }
        }
    }
}

SCENARIO("A sphere is behind a Ray.") {
    GIVEN("r = Ray(point(0, 0, 5), vector(0, 0, 1))")
    AND_GIVEN("s = sphere()") {
        const Ray r{point(0, 0, 5), vector(0, 0, 1)};
        auto s = rtc::sphere();
        WHEN("xs = r.intersect(s)") {
            const auto xs = r.intersect(s);
            THEN("xs.count = 2")
            AND_THEN("xs[0] = -6.0")
            AND_THEN("xs[1] = -4.0") {
                CHECK(xs.size() == 2);
                CHECK(rtc::areFloatsEqual(xs[0].t, -6.0));
                CHECK(rtc::areFloatsEqual(xs[1].t, -4.0));
            }
        }
    }
}

SCENARIO("Intersect sets the object on the intersection.") {
    GIVEN("r = Ray(point(0, 0, -5), vector(0, 0, 1))")
    AND_GIVEN("s = sphere()") {
        const Ray r{point(0, 0, -5), vector(0, 0, 1)};
        auto s = rtc::sphere();
        WHEN("xs = r.intersect(s)") {
            const auto xs = r.intersect(s);
            THEN("xs.count = 2")
            AND_THEN("xs[0].object = s")
            AND_THEN("xs[1].object = s") {
                CHECK(xs.size() == 2);
                const auto s1 = dynamic_cast<rtc::Sphere *>(xs[0].object);
                CHECK(*s1 == s);
                const auto s2 = dynamic_cast<rtc::Sphere *>(xs[1].object);
                CHECK(*s2 == s);
            }
        }
    }
}

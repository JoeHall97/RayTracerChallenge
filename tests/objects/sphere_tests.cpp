#include <RayTracerChallenge/objects/intersection.hpp>
#include <RayTracerChallenge/objects/ray.hpp>
#include <RayTracerChallenge/objects/sphere.hpp>
#include <catch2/catch_test_macros.hpp>

using rtc::Ray, rtc::point, rtc::vector, rtc::sphere;

SCENARIO("Intersecting a scaled sphere with a ray.") {
    GIVEN("r = Ray(point(0, 0, -5), vector(0, 0, 1 ))")
    AND_GIVEN("s = sphere()") {
        const Ray r{point(0, 0, -5), vector(0, 0, 1)};
        auto s = sphere();
        WHEN("s.transform = scaling(2, 2, 2)")
        AND_WHEN("xs = r.intersect(s)") {
            s.transform = rtc::scalingMatrix(2, 2, 2);
            const auto xs = s.intersect(r);
            THEN("xs.count = 2") {
                CHECK(xs.size() == 2);
                CHECK(xs.find(rtc::Intersection{3, &s}) != --xs.end());
                CHECK(xs.find(rtc::Intersection{7, &s}) != --xs.end());
            }
        }
    }
}

SCENARIO("Intersecting a translated sphere with a ray.") {
    GIVEN("r = Ray(point(0, 0, -5), vector(0, 0, 1 ))")
    AND_GIVEN("s = sphere()") {
        const Ray r{point(0, 0, -5), vector(0, 0, 1)};
        auto s = sphere();
        WHEN("s.transform = translation(5, 0, 0)")
        AND_WHEN("xs = r.intersect(s)") {
            s.transform = rtc::translationMatrix(5, 0, 0);
            const auto xs = s.intersect(r);
            THEN("xs.count = 0") {
                CHECK(xs.empty());
            }
        }
    }
}

SCENARIO("A Ray intersects a sphere at two points.") {
    GIVEN("r = Ray(point(0, 0, -5), vector(0, 0, 1))")
    AND_GIVEN("s = sphere()") {
        const Ray r{point(0, 0, -5), vector(0, 0, 1)};
        const auto s = sphere();
        WHEN("xs = r.intersect(s)") {
            const auto xs = s.intersect(r);
            THEN("xs.count = 2")
            AND_THEN("xs[0] = 4.0")
            AND_THEN("xs[1] = 6.0") {
                CHECK(xs.size() == 2);
                CHECK(xs.begin()->t == 4.0);
                CHECK((--xs.end())->t == 6.0);
            }
        }
    }
}

SCENARIO("A Ray intersects a sphere at a tangent.") {
    GIVEN("r = Ray(point(0, 1, -5), vector(0, 0, 1))")
    AND_GIVEN("s = sphere()") {
        const Ray r{point(0, 1, -5), vector(0, 0, 1)};
        auto s = sphere();
        WHEN("xs = r.intersect(s)") {
            const auto xs = s.intersect(r);
            THEN("xs.count = 2")
            AND_THEN("xs[0] = 5.0")
            AND_THEN("xs[1] = 5.0") {
                CHECK(xs.size() == 2);
                CHECK(xs.begin()->t == 5.0);
                CHECK((--xs.end())->t == 5.0);
            }
        }
    }
}

SCENARIO("A Ray that misses a sphere.") {
    GIVEN("r = Ray(point(0, 2, -5), vector(0, 0, 1))")
    AND_GIVEN("s = sphere()") {
        const Ray r{point(0, 2, -5), vector(0, 0, 1)};
        auto s = sphere();
        WHEN("xs = r.intersect(s)") {
            const auto xs = s.intersect(r);
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
        auto s = sphere();
        WHEN("xs = r.intersect(s)") {
            const auto xs = s.intersect(r);
            THEN("xs.count = 2")
            AND_THEN("xs[0] = -1.0")
            AND_THEN("xs[1] = 1.0") {
                CHECK(xs.size() == 2);
                CHECK(rtc::areFloatsEqual(xs.begin()->t, -1.0));
                CHECK((--xs.end())->t == 1.0);
            }
        }
    }
}

SCENARIO("A sphere is behind a Ray.") {
    GIVEN("r = Ray(point(0, 0, 5), vector(0, 0, 1))")
    AND_GIVEN("s = sphere()") {
        const Ray r{point(0, 0, 5), vector(0, 0, 1)};
        auto s = sphere();
        WHEN("xs = r.intersect(s)") {
            const auto xs = s.intersect(r);
            THEN("xs.count = 2")
            AND_THEN("xs[0] = -6.0")
            AND_THEN("xs[1] = -4.0") {
                CHECK(xs.size() == 2);
                CHECK(rtc::areFloatsEqual(xs.begin()->t, -6.0));
                CHECK(rtc::areFloatsEqual((--xs.end())->t, -4.0));
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
            const auto xs = s.intersect(r);
            THEN("xs.count = 2")
            AND_THEN("xs[0].object = s")
            AND_THEN("xs[1].object = s") {
                CHECK(xs.size() == 2);
                const auto s1 = dynamic_cast<const rtc::Sphere *>(xs.begin()->object);
                CHECK(*s1 == s);
                const auto s2 = dynamic_cast<const rtc::Sphere *>((--xs.end())->object);
                CHECK(*s2 == s);
            }
        }
    }
}

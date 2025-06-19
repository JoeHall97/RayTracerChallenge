#include <catch2/catch_test_macros.hpp>

#include "intersection.hpp"
#include "sphere.hpp"

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
            THEN("i = i1") {
                CHECK((i.has_value() && i.value() == i1));
            }
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
            THEN("i = i2") {
                CHECK((i.has_value() && i.value() == i2));
            }
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
            THEN("i = nothing") {
                CHECK(!i.has_value());
            }
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
            THEN("i = nothing") {
                CHECK((i.has_value() && i.value() == i4));
            }
        }
    }
}

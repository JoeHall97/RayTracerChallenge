#pragma once

#include <RayTracerChallenge/datastructures/coord_tuple.hpp>
#include <RayTracerChallenge/datastructures/matrix.hpp>
#include <RayTracerChallenge/helpers/helpers.hpp>
#include <RayTracerChallenge/objects/intersection.hpp>
#include <RayTracerChallenge/objects/object.hpp>
#include <RayTracerChallenge/objects/ray.hpp>

namespace rtc {
    struct Sphere final : Object {
        CoordTuple origin;
        float radius;
        Matrix transform;

        Sphere(const CoordTuple origin, const float radius) : origin{origin}, radius{radius}, transform{identity(4)} {
        }

        Sphere(const CoordTuple origin, const float radius, Matrix &transform) :
            origin{origin}, radius{radius}, transform{transform} {
        }

        bool operator==(const Sphere &rhs) const noexcept {
            return origin == rhs.origin && areFloatsEqual(radius, rhs.radius);
        }
        bool operator==(const Object &rhs) const override {
            if (const auto s = dynamic_cast<const Sphere *>(&rhs); s != nullptr)
                return origin == s->origin && areFloatsEqual(radius, s->radius);
            return false;
        }

        bool operator!=(const Sphere &rhs) const noexcept {
            return !(*this == rhs);
        }

        [[nodiscard]] SortedIntersections intersect(const Ray &ray) const;
    };
    inline Sphere sphere() {
        return Sphere{point(0, 0, 0), 1};
    }
} // namespace rtc

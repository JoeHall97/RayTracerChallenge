#pragma once

#include <RayTracerChallenge/datastructures/coord_tuple.hpp>
#include <RayTracerChallenge/datastructures/matrix.hpp>

namespace rtc {
    struct Ray {
    public:
        CoordTuple origin;
        CoordTuple direction;

        Ray(const CoordTuple origin, const CoordTuple direction) : origin{origin}, direction{direction} {
        }

        [[nodiscard]]
        inline CoordTuple position(const float time) const {
            return origin + direction * time;
        }

        [[nodiscard]]
        Ray transform(const Matrix &m) const;
    };
} // namespace rtc

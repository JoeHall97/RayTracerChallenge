#pragma once

#include <vector>
#include "coord_tuple.hpp"
#include "intersection.hpp"
#include "sphere.hpp"

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

        /// @brief Calculates the intersection(s) with the given sphere.
        /// @param s The sphere to check for intersection with.
        /// @returns The intersection(s) with the given sphere.
        [[nodiscard]]
        std::vector<Intersection> intersect(Sphere &s) const;
    };
} // namespace rtc

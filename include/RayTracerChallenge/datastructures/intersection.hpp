#pragma once

#include <optional>
#include <ostream>
#include <set>

#include "helpers.hpp"
#include "object.hpp"

namespace rtc {
    struct Intersection {
        float t;
        Object *object;

        Intersection(const float t, Object *o) : t{t}, object{o} {
        }

        bool operator==(const Intersection &other) const noexcept {
            return areFloatsEqual(t, other.t) && object == other.object;
        }
    };

    struct IntersectionCompare {
        inline bool operator()(const Intersection &lhs, const Intersection &rhs) const {
            return lhs.t < rhs.t;
        }
    };

    // a sorted set of Intersections by t ascending
    using SortedIntersections = std::set<Intersection, IntersectionCompare>;

    std::optional<Intersection> hit(const SortedIntersections &intersections);
} // namespace rtc

std::ostream &operator<<(std::ostream &os, const rtc::Intersection &i);

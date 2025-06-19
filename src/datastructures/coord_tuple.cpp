#include "coord_tuple.hpp"

#include <algorithm>
#include <cmath>
#include <ostream>

#include "helpers.hpp"

using rtc::CoordTuple;

bool CoordTuple::operator==(const CoordTuple &rhs) const {
    return w == rhs.w && rtc::areFloatsEqual(x, rhs.x) && rtc::areFloatsEqual(y, rhs.y) &&
           rtc::areFloatsEqual(z, rhs.z);
}

CoordTuple CoordTuple::operator+(const CoordTuple &rhs) const {
    return CoordTuple{x + rhs.x, y + rhs.y, z + rhs.z, std::max(w, rhs.w)};
}

CoordTuple CoordTuple::operator-(const CoordTuple &rhs) const {
    return CoordTuple{x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w};
}

CoordTuple CoordTuple::operator-() const {
    return CoordTuple{-x, -y, -z, -w};
}

CoordTuple CoordTuple::operator*(const float value) const {
    return CoordTuple{x * value, y * value, z * value, w * value};
}

CoordTuple CoordTuple::operator/(const float value) const {
    return CoordTuple{x / value, y / value, z / value, w / value};
}

float CoordTuple::magnitude() const {
    return static_cast<float>(std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2) + std::pow(w, 2)));
}

CoordTuple CoordTuple::normalise() const {
    const auto mag = magnitude();
    return CoordTuple{x / mag, y / mag, z / mag, w / mag};
}

float CoordTuple::dot(const CoordTuple &b) const {
    return x * b.x + y * b.y + z * b.z + w * b.w;
}

CoordTuple CoordTuple::cross(const CoordTuple &b) const {
    return CoordTuple{y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x, w};
}

std::ostream &operator<<(std::ostream &os, const CoordTuple &t) {
    os << '{' << t.x << ", " << t.y << ", " << t.z << ", " << t.w << '}';
    return os;
}

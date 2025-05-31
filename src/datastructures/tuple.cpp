#include "tuple.h"
#include "helpers.h"
#include <algorithm>
#include <cmath>
#include <ostream>

bool Tuple::operator==(const Tuple &rhs) const
{
    return w == rhs.w && areFloatsEqual(x, rhs.x) && areFloatsEqual(y, rhs.y) && areFloatsEqual(z, rhs.z);
}

Tuple Tuple::operator+(const Tuple &rhs) const
{
    return Tuple{x + rhs.x, y + rhs.y, z + rhs.z, std::max(w, rhs.w)};
}

Tuple Tuple::operator-(const Tuple &rhs) const
{
    return Tuple{x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w};
}

Tuple Tuple::operator-() const
{
    return Tuple{-x, -y, -z, -w};
}

Tuple Tuple::operator*(const float value) const
{
    return Tuple{x * value, y * value, z * value, w * value};
}

Tuple Tuple::operator/(const float value) const
{
    return Tuple{x / value, y / value, z / value, w / value};
}

float Tuple::magnitude() const
{
    return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2) + std::pow(w, 2));
}

Tuple Tuple::normarilise() const
{
    auto mag = magnitude();
    return Tuple{x / mag, y / mag, z / mag, w / mag};
}

float Tuple::dot(const Tuple &b) const
{
    return x * b.x + y * b.y + z * b.z + w * b.w;
}

Tuple Tuple::cross(const Tuple &b) const
{
    return Tuple{y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x, w};
}

std::ostream &operator<<(std::ostream &os, const Tuple &t)
{
    os << '{' << t.x << ", " << t.y << ", " << t.z << ", " << t.w << '}';
    return os;
}

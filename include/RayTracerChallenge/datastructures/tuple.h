#pragma once

#include <ostream>
class Tuple
{
  public:
    float x, y, z, w;

    Tuple(const float x, const float y, const float z, const float w) : x{x}, y{y}, z{z}, w{w}
    {
    }
    Tuple() = delete;

    bool operator==(const Tuple &rhs) const;
    Tuple operator+(const Tuple &rhs) const;
    Tuple operator-(const Tuple &rhs) const;
    Tuple operator-() const;
    Tuple operator*(const float value) const;
    Tuple operator/(const float value) const;

    [[nodiscard]] inline bool isVector() const
    {
        return w == 0;
    }
    [[nodiscard]] inline bool isPoint() const
    {
        return w == 1;
    }

    float magnitude() const;
    Tuple normarilise() const;
    float dot(const Tuple &b) const;
    Tuple cross(const Tuple &b) const;
};

std::ostream &operator<<(std::ostream &os, const Tuple &t);

inline Tuple point(const float x, const float y, const float z)
{
    return Tuple{x, y, z, 1};
}
inline Tuple vector(const float x, const float y, const float z)
{
    return Tuple{x, y, z, 0};
}

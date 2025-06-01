#pragma once

#include <ostream>
class CoordTuple
{
  public:
    float x, y, z, w;

    CoordTuple(const float x, const float y, const float z, const float w) : x{x}, y{y}, z{z}, w{w}
    {
    }
    CoordTuple() = delete;

    bool operator==(const CoordTuple &rhs) const;
    CoordTuple operator+(const CoordTuple &rhs) const;
    CoordTuple operator-(const CoordTuple &rhs) const;
    CoordTuple operator-() const;
    CoordTuple operator*(const float value) const;
    CoordTuple operator/(const float value) const;

    [[nodiscard]] inline bool isVector() const
    {
        return w == 0;
    }
    [[nodiscard]] inline bool isPoint() const
    {
        return w == 1;
    }

    float magnitude() const;
    CoordTuple normarilise() const;
    float dot(const CoordTuple &b) const;
    CoordTuple cross(const CoordTuple &b) const;
};

std::ostream &operator<<(std::ostream &os, const CoordTuple &t);

inline CoordTuple point(const float x, const float y, const float z)
{
    return CoordTuple{x, y, z, 1};
}
inline CoordTuple vector(const float x, const float y, const float z)
{
    return CoordTuple{x, y, z, 0};
}

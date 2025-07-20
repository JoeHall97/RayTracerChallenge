#pragma once
#include <ostream>

namespace rtc {
    struct ColourTuple {
    public:
        float red, green, blue;

        ColourTuple(const float red, const float green, const float blue) : red{red}, green{green}, blue{blue} {
        }

        bool operator==(const ColourTuple &rhs) const;
        ColourTuple operator+(const ColourTuple &rhs) const;
        ColourTuple operator-(const ColourTuple &rhs) const;
        ColourTuple operator*(const float &value) const;
        ColourTuple operator*(const ColourTuple &rhs) const;
    };
} // namespace rtc

std::ostream &operator<<(std::ostream &os, const rtc::ColourTuple &t);

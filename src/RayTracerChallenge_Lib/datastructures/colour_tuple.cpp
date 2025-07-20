#include <RayTracerChallenge/datastructures/colour_tuple.hpp>
#include <RayTracerChallenge/helpers/helpers.hpp>
#include <ostream>


using rtc::ColourTuple;

bool ColourTuple::operator==(const ColourTuple &rhs) const {
    return areFloatsEqual(red, rhs.red) && areFloatsEqual(green, rhs.green) && areFloatsEqual(blue, rhs.blue);
}

ColourTuple ColourTuple::operator+(const ColourTuple &rhs) const {
    return ColourTuple{red + rhs.red, green + rhs.green, blue + rhs.blue};
}

ColourTuple ColourTuple::operator-(const ColourTuple &rhs) const {
    return ColourTuple{red - rhs.red, green - rhs.green, blue - rhs.blue};
}

ColourTuple ColourTuple::operator*(const float &value) const {
    return ColourTuple{red * value, green * value, blue * value};
}

ColourTuple ColourTuple::operator*(const ColourTuple &rhs) const {
    return ColourTuple{red * rhs.red, green * rhs.green, blue * rhs.blue};
}

std::ostream &operator<<(std::ostream &os, const ColourTuple &t) {
    os << '{' << t.red << ", " << t.green << ", " << t.blue << '}';
    return os;
}

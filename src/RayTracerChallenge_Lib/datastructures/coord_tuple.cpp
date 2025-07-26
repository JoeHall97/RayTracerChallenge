#include <RayTracerChallenge/datastructures/coord_tuple.hpp>
#include <ostream>

std::ostream &operator<<(std::ostream &os, const rtc::CoordTuple &t) {
  os << '{' << t.x << ", " << t.y << ", " << t.z << ", " << t.w << '}';
  return os;
}

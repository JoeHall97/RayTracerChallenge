#include <RayTracerChallenge/datastructures/colour_tuple.hpp>
#include <ostream>

std::ostream &operator<<(std::ostream &os, const rtc::ColourTuple &t) {
  os << '{' << t.red << ", " << t.green << ", " << t.blue << '}';
  return os;
}

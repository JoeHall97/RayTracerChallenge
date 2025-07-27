#include <RayTracerChallenge/objects/colour.hpp>
#include <ostream>

std::ostream &operator<<(std::ostream &os, const rtc::Colour &t) {
  os << '{' << t.red << ", " << t.green << ", " << t.blue << '}';
  return os;
}

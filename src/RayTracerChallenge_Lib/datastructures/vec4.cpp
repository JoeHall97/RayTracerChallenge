#include <RayTracerChallenge/datastructures/vec4.hpp>
#include <ostream>

std::ostream &operator<<(std::ostream &os, const rtc::Vec4 &t) {
  os << '{' << t.x << ", " << t.y << ", " << t.z << ", " << t.w << '}';
  return os;
}

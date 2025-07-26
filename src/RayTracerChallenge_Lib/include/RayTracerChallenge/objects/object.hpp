#pragma once

namespace rtc {
struct Object {
  virtual ~Object() = default;
  Object() = default;
  virtual bool operator==(const Object &other) const = 0;
};
} // namespace rtc

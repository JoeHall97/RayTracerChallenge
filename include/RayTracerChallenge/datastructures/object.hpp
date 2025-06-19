#pragma once

namespace rtc {
struct Object {
  Object() = default;
  virtual ~Object() = default;
  virtual bool operator==(const Object &other) const = 0;
};
}  // namespace rtc

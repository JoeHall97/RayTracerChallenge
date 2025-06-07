#include "canvas.hpp"

#include <iostream>
#include <sstream>

inline int getDigitCount(int number) {
  if (number == 0) return 1;
  return ((int)std::log10(number)) + 1;
}

/// @brief Adds the given number to the string stream and makes sure that adding
/// the number does not cause the current line to exceed 70 characters in
/// length. If the number would exceed the 70 character length, then a new line
/// is output and the row length is reset.
/// @param ss The stream to output the number to.
/// @param number The number to output.
/// @param charCount The current number of characters in the current line.
inline void checkAndAddNumber(std::stringstream &ss, const float &number,
                              int &charCount) {
  int num = std::max(0, std::min(255, (int)std::round(255 * number)));
  auto digits = getDigitCount(num);
  if (digits < 0) {
    std::cout << digits << ' ' << num << '\n';
  }
  if (charCount + digits + 1 >= 70) {
    ss << '\n';
    charCount = 0;
  } else if (charCount != 0) {
    ss << ' ';
    charCount += 1;
  }
  ss << num;
  charCount += digits;
}

bool Canvas::writePixel(uint16_t x, uint16_t y, ColourTuple colour) {
  if (x > width || x < 0 || y > height || y < 0) {
    return false;
  }
  canvas[y][x] = colour;
  return true;
}

std::string Canvas::toPPM() const {
  std::stringstream ss;
  // header
  ss << "P3\n" << width << ' ' << height << "\n255\n";
  // body
  for (auto &row : canvas) {
    int charCount = 0;
    for (auto &column : row) {
      checkAndAddNumber(ss, column.red, charCount);
      checkAndAddNumber(ss, column.green, charCount);
      checkAndAddNumber(ss, column.blue, charCount);
    }
    ss << '\n';
  }
  return ss.str();
}

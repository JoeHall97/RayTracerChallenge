#pragma once
#include <vector>

#include "colour_tuple.hpp"

namespace rtc {
struct Canvas {
 public:
  std::vector<std::vector<ColourTuple>> canvas;
  uint16_t width, height;

  Canvas(uint16_t width, uint16_t height) : width{width}, height{height} {
    canvas = std::vector<std::vector<ColourTuple>>(
        height, std::vector<ColourTuple>(width, ColourTuple{0, 0, 0}));
  }

  Canvas(uint16_t width, uint16_t height, ColourTuple defaultColour)
      : width{width}, height{height} {
    canvas = std::vector<std::vector<ColourTuple>>(
        height, std::vector<ColourTuple>(width, defaultColour));
  }

  /// @brief Sets the colour at the given x, y position on the canvas.
  /// @param x
  /// @param y
  /// @param colour
  /// @return true if the colour was added to the canvas, else false
  bool writePixel(uint16_t x, uint16_t y, ColourTuple colour);
  /// @brief Output the canvas as a .ppm string.
  /// @return
  std::string toPPM() const;
};
}  // namespace rtc

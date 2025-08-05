#pragma once
#include <RayTracerChallenge/objects/colour.hpp>
#include <vector>

namespace rtc {
class Canvas {
public:
  Canvas(const std::size_t width, const std::size_t height)
      : width{width}, height{height} {
    canvas = std::vector(height, std::vector(width, Colour{0, 0, 0}));
  }

  Canvas(const std::size_t width, const std::size_t height,
         const Colour defaultColour)
      : width{width}, height{height} {
    canvas = std::vector(height, std::vector(width, defaultColour));
  }

  /// @brief Sets the colour at the given x, y position on the canvas.
  /// @param x
  /// @param y
  /// @param colour
  /// @return true if the colour was added to the canvas, else false
  bool writePixel(const std::size_t x, const std::size_t y,
                  const Colour &colour) {
    if (x > width || y > height) {
      return false;
    }
    canvas[y][x] = colour;
    return true;
  }

  /// @brief Output the canvas as a .ppm string.
  /// @return
  [[nodiscard]] std::string toPPM() const;

  [[nodiscard]] Colour getPixel(const std::size_t x,
                                const std::size_t y) const {
    return canvas[y][x];
  }

private:
  std::vector<std::vector<Colour>> canvas;
  std::size_t width, height;
};
} // namespace rtc

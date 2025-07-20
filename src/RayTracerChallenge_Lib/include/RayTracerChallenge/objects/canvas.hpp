#pragma once
#include <cstdint>
#include <RayTracerChallenge/datastructures/colour_tuple.hpp>
#include <vector>

namespace rtc {
    struct Canvas {
    public:
        std::vector<std::vector<ColourTuple>> canvas;
        std::uint16_t width, height;

        Canvas(const std::uint16_t width, const std::uint16_t height) : width{width}, height{height} {
            canvas = std::vector(height, std::vector<ColourTuple>(width, ColourTuple{0, 0, 0}));
        }

        Canvas(const std::uint16_t width, const std::uint16_t height, const ColourTuple defaultColour) :
            width{width}, height{height} {
            canvas = std::vector(height, std::vector(width, defaultColour));
        }

        /// @brief Sets the colour at the given x, y position on the canvas.
        /// @param x
        /// @param y
        /// @param colour
        /// @return true if the colour was added to the canvas, else false
        bool writePixel(uint16_t x, uint16_t y, ColourTuple colour);
        /// @brief Output the canvas as a .ppm string.
        /// @return
        [[nodiscard]]
        std::string toPPM() const;
    };
} // namespace rtc

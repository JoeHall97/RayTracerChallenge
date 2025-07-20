#include <RayTracerChallenge/datastructures/colour_tuple.hpp>
#include <RayTracerChallenge/objects/canvas.hpp>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <sstream>

namespace {
    inline int getDigitCount(const int number) {
        if (number == 0)
            return 1;
        return static_cast<int>(std::log10(number)) + 1;
    }

    /// @brief Adds the given number to the string stream and makes sure that adding
    /// the number does not cause the current line to exceed 70 characters in
    /// length. If the number would exceed the 70 character length, then a new line
    /// is output and the row length is reset.
    /// @param ss The stream to output the number to.
    /// @param number The number to output.
    /// @param charCount The current number of characters in the current line.
    inline void checkAndAddNumber(std::stringstream &ss, const float &number, int &charCount) {
        const int num = std::max(0, std::min(255, static_cast<int>(std::round(255 * number))));
        const auto digits = getDigitCount(num);
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
} // namespace

bool rtc::Canvas::writePixel(const std::uint16_t x, const std::uint16_t y, const ColourTuple colour) {
    if (x > width || y > height) {
        return false;
    }
    canvas[y][x] = colour;
    return true;
}

std::string rtc::Canvas::toPPM() const {
    std::stringstream ss;
    // header
    ss << "P3\n" << width << ' ' << height << "\n255\n";
    // body
    for (auto &row: canvas) {
        int charCount = 0;
        for (auto &column: row) {
            checkAndAddNumber(ss, column.red, charCount);
            checkAndAddNumber(ss, column.green, charCount);
            checkAndAddNumber(ss, column.blue, charCount);
        }
        ss << '\n';
    }
    return ss.str();
}

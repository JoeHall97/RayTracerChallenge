#include <fstream>
#include <iostream>
#include <numbers>

#include "canvas.hpp"
#include "colour_tuple.hpp"
#include "coord_tuple.hpp"
#include "matrix.hpp"

#include <cstdint>

int main() {
    constexpr uint16_t WIDTH = 100;
    constexpr uint16_t HEIGHT = 100;
    constexpr float RADIUS = static_cast<float>(WIDTH) * 0.33;

    rtc::Canvas canvas{WIDTH, HEIGHT};
    const auto canvasOrigin = rtc::point(static_cast<float>(WIDTH) / 2.0, static_cast<float>(HEIGHT) / 2.0, 0);
    const auto twelve = rtc::point(0, 1, 0);
    const rtc::ColourTuple blue{0, 0, 1};

    // write the center pixel of the canvas
    canvas.writePixel(static_cast<uint16_t>(canvasOrigin.x), canvas.height - static_cast<uint16_t>(canvasOrigin.y),
                      blue);

    // starting with twelve o'clock, rotate around the circle's perimeter.
    // each step is 1/12th the circle diameter, giving us a clock face.
    for (uint8_t i = 0; i < 12; ++i) {
        const auto rotation = rtc::rotationMatrixZ(static_cast<float>(i) * std::numbers::pi_v<float> / 6.0f);
        auto point = rotation * twelve;
        point.x *= RADIUS;
        point.y *= RADIUS;
        point = point + canvasOrigin;
        if (!canvas.writePixel(static_cast<uint16_t>(point.x), canvas.height - static_cast<uint16_t>(point.y), blue))
            std::cout << "ERROR\n" << point << '\n';
    }

    std::ofstream file;
    file.open("test.ppm");
    file << canvas.toPPM();
    file.close();
    return 0;
}

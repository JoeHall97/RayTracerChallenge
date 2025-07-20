#include <RayTracerChallenge/datastructures/colour_tuple.hpp>
#include <RayTracerChallenge/datastructures/coord_tuple.hpp>
#include <RayTracerChallenge/datastructures/matrix.hpp>
#include <RayTracerChallenge/objects/canvas.hpp>
#include <RayTracerChallenge/objects/sphere.hpp>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <numbers>

int main() {
    constexpr std::uint16_t PIXELS = 100;
    rtc::Canvas canvas{PIXELS, PIXELS};
    const rtc::ColourTuple GREEN{0, 1, 0};
    const auto SPHERE = rtc::sphere();
    const auto WALL_Z = 10.0f;
    const auto WALL_SIZE = 8.0f;
    const auto PIXEL_SIZE = WALL_SIZE / PIXELS;
    const auto HALF = WALL_SIZE / 2;
    const auto RAY_ORIGIN = rtc::point(0, 0, -5);

    for (std::uint16_t y = 0; y < PIXELS; ++y) {
        const auto worldY = HALF - PIXEL_SIZE * static_cast<float>(y);
        for (std::uint16_t x = 0; x < PIXELS; ++x) {
            const auto worldX = -HALF - PIXEL_SIZE * static_cast<float>(x);
            const auto position = rtc::point(worldX, worldY, WALL_Z);
            const rtc::Ray r{RAY_ORIGIN, position};
            if (const auto xs = SPHERE.intersect(r); rtc::hit(xs)) {
                canvas.writePixel(x, y, GREEN);
            }
        }
    }

    std::ofstream file;
    file.open("test.ppm");
    file << canvas.toPPM();
    file.close();
    return 0;
}

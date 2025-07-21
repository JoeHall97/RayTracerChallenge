#include <RayTracerChallenge/datastructures/colour_tuple.hpp>
#include <RayTracerChallenge/datastructures/coord_tuple.hpp>
#include <RayTracerChallenge/datastructures/matrix.hpp>
#include <RayTracerChallenge/objects/canvas.hpp>
#include <RayTracerChallenge/objects/intersection.hpp>
#include <RayTracerChallenge/objects/ray.hpp>
#include <RayTracerChallenge/objects/sphere.hpp>
#include <cstdint>
#include <fstream>
#include <iostream>

int main() {
    constexpr std::uint16_t PIXELS = 100;
    constexpr auto WALL_Z = 10.0f;
    constexpr auto WALL_SIZE = 10.0f;
    constexpr auto PIXEL_SIZE = WALL_SIZE / PIXELS;
    constexpr auto HALF_WALL_SIZE = WALL_SIZE / 2;

    const rtc::ColourTuple green{0, 1, 0};
    const auto rayOrigin = rtc::point(0, 0, -5);
    const auto shape = rtc::sphere();
    rtc::Canvas canvas{PIXELS, PIXELS};

    for (auto y = 0; y < PIXELS; ++y) {
        const auto worldY = HALF_WALL_SIZE - PIXEL_SIZE * y;
        for (auto x = 0; x < PIXELS; ++x) {
            const auto worldX = -HALF_WALL_SIZE + PIXEL_SIZE * x;
            const auto position = rtc::point(worldX, worldY, WALL_Z);
            const rtc::Ray ray{rayOrigin, (position - rayOrigin).normalise()};
            const auto xs = shape.intersect(ray);

            if (rtc::hit(xs).has_value()) {
                canvas.writePixel(x, y, green);
            }
        }
    }

    std::ofstream file;
    file.open("test.ppm");
    file << canvas.toPPM();
    file.close();
    return 0;
}

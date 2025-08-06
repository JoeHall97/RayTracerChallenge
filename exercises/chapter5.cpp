#include <RayTracerChallenge/datastructures/vec4.hpp>
#include <RayTracerChallenge/objects/canvas.hpp>
#include <RayTracerChallenge/objects/colour.hpp>
#include <RayTracerChallenge/objects/intersection.hpp>
#include <RayTracerChallenge/objects/ray.hpp>
#include <RayTracerChallenge/objects/sphere.hpp>
#include <fstream>

int main() {
  constexpr std::size_t PIXELS = 100;
  constexpr auto WALL_SIZE = 10.0f;
  constexpr auto PIXEL_SIZE = WALL_SIZE / PIXELS;
  constexpr auto HALF_WALL_SIZE = WALL_SIZE / 2;

  const rtc::Colour green{0, 1, 0};
  const auto rayOrigin = rtc::point(0, 0, -5);
  const auto shape = rtc::sphere();
  rtc::Canvas canvas{PIXELS, PIXELS};

  for (auto y = 0; y < PIXELS; ++y) {
    const auto worldY = HALF_WALL_SIZE - PIXEL_SIZE * static_cast<float>(y);
    for (auto x = 0; x < PIXELS; ++x) {
      constexpr auto WALL_Z = 10.0f;
      const auto worldX = -HALF_WALL_SIZE + PIXEL_SIZE * static_cast<float>(x);
      const auto position = rtc::point(worldX, worldY, WALL_Z);
      const rtc::Ray ray{rayOrigin, (position - rayOrigin).normalise()};

      if (const auto xs = shape.intersect(ray); rtc::hit(xs).has_value()) {
        canvas.writePixel(x, y, green);
      }
    }
  }

  std::ofstream file;
  file.open("Chapter5.ppm");
  file << canvas.toPPM();
  file.close();
  return 0;
}
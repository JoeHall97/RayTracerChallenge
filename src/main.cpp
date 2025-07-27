#include <RayTracerChallenge/datastructures/matrix.hpp>
#include <RayTracerChallenge/datastructures/vec4.hpp>
#include <RayTracerChallenge/objects/canvas.hpp>
#include <RayTracerChallenge/objects/colour.hpp>
#include <RayTracerChallenge/objects/intersection.hpp>
#include <RayTracerChallenge/objects/ray.hpp>
#include <RayTracerChallenge/objects/sphere.hpp>
#include <cstdint>
#include <fstream>

int main() {
  constexpr std::uint16_t PIXELS = 100;
  constexpr auto WALL_Z = 10.0f;
  constexpr auto WALL_SIZE = 10.0f;
  constexpr auto PIXEL_SIZE = WALL_SIZE / PIXELS;
  constexpr auto HALF_WALL_SIZE = WALL_SIZE / 2;

  const rtc::Colour green{0, 1, 0};
  const auto rayOrigin = rtc::point(0, 0, -5);
  auto shape = rtc::sphere();
  shape.material.colour = rtc::Colour{0.3, 0.2, 1};
  shape.transform = rtc::scalingMatrix(1.3, 0.4, 1);
  const rtc::Light light{rtc::Colour{1, 1, 1}, rtc::point(-10, 10, -10)};
  rtc::Canvas canvas{PIXELS, PIXELS};

  for (auto y = 0; y < PIXELS; ++y) {
    const auto worldY = HALF_WALL_SIZE - PIXEL_SIZE * y;
    for (auto x = 0; x < PIXELS; ++x) {
      const auto worldX = -HALF_WALL_SIZE + PIXEL_SIZE * x;
      const auto position = rtc::point(worldX, worldY, WALL_Z);
      const rtc::Ray ray{rayOrigin, (position - rayOrigin).normalise()};
      const auto xs = shape.intersect(ray);
      const auto hit = rtc::hit(xs);

      if (hit.has_value()) {
        const auto point = ray.position(hit->t);
        const auto normal = shape.normalAt(point);
        const auto eye = -ray.direction;
        const auto colour = shape.material.lighting(light, point, eye, normal);
        canvas.writePixel(x, y, colour);
      }
    }
  }

  std::ofstream file;
  file.open("test.ppm");
  file << canvas.toPPM();
  file.close();
  return 0;
}

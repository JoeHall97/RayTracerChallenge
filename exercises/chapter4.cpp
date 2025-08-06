#include <RayTracerChallenge/datastructures/matrix.hpp>
#include <RayTracerChallenge/datastructures/vec4.hpp>
#include <RayTracerChallenge/objects/canvas.hpp>
#include <RayTracerChallenge/objects/colour.hpp>
#include <fstream>
#include <iostream>
#include <numbers>

int main() {
  constexpr std::size_t WIDTH = 100;
  constexpr std::size_t HEIGHT = 100;
  constexpr float RADIUS = WIDTH * 0.33f;

  rtc::Canvas canvas{WIDTH, HEIGHT};
  const auto canvasOrigin = rtc::point(WIDTH / 2.0f, HEIGHT / 2.0f, 0);
  const auto twelve = rtc::point(0, 1, 0);
  const rtc::Colour blue{0, 0, 1};

  // write the center pixel of the canvas
  canvas.writePixel(
      static_cast<std::size_t>(canvasOrigin.x),
      canvas.getHeight() - static_cast<std::size_t>(canvasOrigin.y), blue);

  // starting with twelve o'clock, rotate around the circle's perimeter.
  // each step is 1/12th the circle's diameter, giving us a clock face.
  for (auto i = 0; i < 12; ++i) {
    const auto rotation = rtc::rotationMatrixZ(
        static_cast<float>(i) * std::numbers::pi_v<float> / 6.0f);
    auto point = rotation * twelve;
    point.x *= RADIUS;
    point.y *= RADIUS;
    point = point + canvasOrigin;
    if (!canvas.writePixel(
        static_cast<std::size_t>(point.x),
        canvas.getHeight() - static_cast<std::size_t>(point.y), blue))
      std::cout << "ERROR\n" << point << '\n';
  }

  std::ofstream file;
  file.open("Chapter4.ppm");
  file << canvas.toPPM();
  file.close();
  return 0;
}
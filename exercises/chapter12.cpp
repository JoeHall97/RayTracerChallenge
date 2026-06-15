#include "RayTracerChallenge/datastructures/matrix.hpp"
#include "RayTracerChallenge/datastructures/vec4.hpp"
#include "RayTracerChallenge/objects/camera.hpp"
#include "RayTracerChallenge/objects/canvas.hpp"
#include "RayTracerChallenge/objects/colour.hpp"
#include "RayTracerChallenge/objects/cube.hpp"
#include "RayTracerChallenge/objects/light.hpp"
#include "RayTracerChallenge/objects/material.hpp"
#include "RayTracerChallenge/objects/patterns.hpp"
#include "RayTracerChallenge/objects/plane.hpp"
#include "RayTracerChallenge/objects/world.hpp"
#include <fstream>
#include <memory>
#include <numbers>

int main() {
  rtc::World world{};

  rtc::Plane plane{};
  auto planeMaterial = plane.getMaterial();
  planeMaterial.colour = rtc::WHITE;
  planeMaterial.transparency = 0.9f;
  planeMaterial.reflective = 0.9f;
  plane.setMaterial(planeMaterial);
  world.objects.push_back(std::make_unique<rtc::Plane>(plane));

  const rtc::Plane leftWall{
      rtc::translationMatrix(0, 0, 5) *
          rtc::rotationMatrixY(-std::numbers::pi_v<float> / 4.0f) *
          rtc::rotationMatrixX(std::numbers::pi_v<float> / 2.0f) *
          rtc::scalingMatrix(10, 0.01f, 10),
      rtc::Material{std::make_unique<rtc::CheckerPattern>(
          rtc::WHITE, rtc::BLACK, rtc::scalingMatrix(0.06f, 0.06f, 0.06f))}};
  world.objects.push_back(std::make_unique<rtc::Plane>(leftWall));

  const rtc::Plane rightWall{
      rtc::translationMatrix(0, 0, 5) *
          rtc::rotationMatrixY(std::numbers::pi_v<float> / 4.0f) *
          rtc::rotationMatrixX(std::numbers::pi_v<float> / 2.0f) *
          rtc::scalingMatrix(10, 0.01f, 10),
      rtc::Material{std::make_unique<rtc::CheckerPattern>(
          rtc::WHITE, rtc::BLACK, rtc::scalingMatrix(0.06f, 0.06f, 0.06f))}};
  world.objects.push_back(std::make_unique<rtc::Plane>(rightWall));

  world.objects.push_back(std::make_unique<rtc::Cube>(
      rtc::translationMatrix(0, 1, 1), rtc::Material{rtc::Colour{0, 1, 0}}));

  world.light = rtc::Light{rtc::WHITE, rtc::point(-10, 10, -10)};

  const rtc::Camera camera{rtc::viewTransform(rtc::point(0, 2.5f, -4.0f),
                                              rtc::point(0, 1, 0),
                                              rtc::vector(0, 1, 0)),
                           300, 300, std::numbers::pi_v<float> / 3.0f};

  const rtc::Canvas canvas = camera.render(world);
  std::ofstream file;
  file.open("image.ppm");
  file << canvas.toPPM();
  file.close();

  return 0;
}

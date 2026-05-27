#include "RayTracerChallenge/objects/patterns.hpp"
#include <RayTracerChallenge/datastructures/matrix.hpp>
#include <RayTracerChallenge/datastructures/vec4.hpp>
#include <RayTracerChallenge/objects/camera.hpp>
#include <RayTracerChallenge/objects/canvas.hpp>
#include <RayTracerChallenge/objects/colour.hpp>
#include <RayTracerChallenge/objects/plane.hpp>
#include <RayTracerChallenge/objects/sphere.hpp>
#include <RayTracerChallenge/objects/world.hpp>
#include <fstream>
#include <numbers>

int main() {
  rtc::World world{};

  auto floor = rtc::plane();
  auto floorMaterial = floor.getMaterial();
  floorMaterial.pattern =
      std::make_unique<rtc::CheckerPattern>(rtc::WHITE, rtc::BLACK);
  floorMaterial.colour = rtc::WHITE;
  floorMaterial.transparency = 0.9f;
  floorMaterial.reflective = 0.9f;
  floor.setMaterial(floorMaterial);
  world.objects.push_back(std::make_unique<rtc::Plane>(floor));

  auto wall = rtc::plane();
  wall.setTransformationMatrix(
      rtc::rotationMatrixX(std::numbers::pi_v<float> / 2) *
      rtc::translationMatrix(0, 10, 20));
  auto wallMaterial = floor.getMaterial();
  wallMaterial.pattern =
      std::make_unique<rtc::RingPattern>(rtc::WHITE, rtc::BLACK);
  wallMaterial.colour = rtc::Colour{0.5, 0.5, 0.5};
  wallMaterial.specular = 0;
  wall.setMaterial(wallMaterial);
  world.objects.push_back(std::make_unique<rtc::Plane>(wall));

  auto middle = rtc::glassSphere();
  middle.setTransformationMatrix(rtc::translationMatrix(0, 2.0f, 0) *
                                 rtc::scalingMatrix(1.5f, 1.5f, 1.5f));
  auto middleMaterial = middle.getMaterial();
  middleMaterial.ambient = 0.01f;
  middleMaterial.diffuse = 0.3f;
  middle.setMaterial(middleMaterial);
  world.objects.push_back(std::make_unique<rtc::Sphere>(middle));

  world.light = rtc::Light{rtc::WHITE, rtc::point(-10, 10, -10)};

  rtc::Camera camera{144, 144, std::numbers::pi_v<float> / 3};
  camera.setTransform(rtc::viewTransform(
      rtc::point(0, 2.5f, -4), rtc::point(0, 1.75f, 0), rtc::vector(0, 1, 0)));

  const rtc::Canvas canvas = camera.render(world);
  std::ofstream file;
  file.open("image.ppm");
  file << canvas.toPPM();
  file.close();
  return 0;
}

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
  floorMaterial.colour = rtc::Colour{0.5, 0.5, 0.5};
  floorMaterial.specular = 0;
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

  auto middle = rtc::sphere();
  middle.setTransformationMatrix(rtc::translationMatrix(-0.5f, 1.25f, 1.2f) *
                                 rtc::scalingMatrix(1.25f, 1.25f, 1.25f));
  auto middleMaterial = middle.getMaterial();
  middleMaterial.pattern =
      std::make_unique<rtc::RingPattern>(rtc::WHITE, rtc::BLACK);
  middleMaterial.pattern->setTransformationMatrix(
      rtc::rotationMatrixX(std::numbers::pi_v<float> / 2) *
      middle.getTransformationMatrix().inverse());
  middleMaterial.colour = rtc::Colour{0.1f, 1, 0.5f};
  middleMaterial.diffuse = 0.7f;
  middleMaterial.specular = 0.3f;
  middle.setMaterial(middleMaterial);
  world.objects.push_back(std::make_unique<rtc::Sphere>(middle));

  auto right = rtc::sphere();
  right.setTransformationMatrix(rtc::translationMatrix(1.5f, 0.5f, -0.5f) *
                                rtc::scalingMatrix(0.5f, 0.5f, 0.5f));
  auto rightMaterial = right.getMaterial();
  rightMaterial.pattern =
      std::make_unique<rtc::GradientPattern>(rtc::WHITE, rtc::BLACK);
  rightMaterial.pattern->setTransformationMatrix(rtc::scalingMatrix(1, 1, 1));
  rightMaterial.colour = rtc::Colour{0.5f, 1, 0.1f};
  rightMaterial.diffuse = 0.7f;
  rightMaterial.specular = 0.3f;
  right.setMaterial(rightMaterial);
  world.objects.push_back(std::make_unique<rtc::Sphere>(right));

  auto left = rtc::sphere();
  left.setTransformationMatrix(rtc::translationMatrix(-1.5f, 0.33f, -0.75f) *
                               rtc::scalingMatrix(0.33f, 0.33f, 0.33f));
  auto leftMaterial = left.getMaterial();
  leftMaterial.pattern =
      std::make_unique<rtc::StripePattern>(rtc::WHITE, rtc::BLACK);
  leftMaterial.pattern->setTransformationMatrix(rtc::scalingMatrix(1, 1, 1));
  leftMaterial.colour = rtc::Colour{1, 0.8f, 0.1f};
  leftMaterial.diffuse = 0.7f;
  leftMaterial.specular = 0.3f;
  left.setMaterial(leftMaterial);
  world.objects.push_back(std::make_unique<rtc::Sphere>(left));

  world.light = rtc::Light{rtc::Colour{1, 1, 1}, rtc::point(-10, 10, -10)};

  rtc::Camera camera{144, 144, std::numbers::pi_v<float> / 3};
  camera.setTransform(rtc::viewTransform(
      rtc::point(0, 1.5f, -5), rtc::point(0, 0.25, 0), rtc::vector(0, 1, 0)));

  const rtc::Canvas canvas = camera.render(world);
  std::ofstream file;
  file.open("image.ppm");
  file << canvas.toPPM();
  file.close();
  return 0;
}

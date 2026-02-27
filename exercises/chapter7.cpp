#include <RayTracerChallenge/datastructures/matrix.hpp>
#include <RayTracerChallenge/datastructures/vec4.hpp>
#include <RayTracerChallenge/objects/camera.hpp>
#include <RayTracerChallenge/objects/canvas.hpp>
#include <RayTracerChallenge/objects/colour.hpp>
#include <RayTracerChallenge/objects/sphere.hpp>
#include <RayTracerChallenge/objects/world.hpp>
#include <fstream>
#include <numbers>

int main() {
  rtc::World world{};

  auto floor = rtc::sphere();
  auto floorMaterial = floor.getMaterial();
  floorMaterial.colour = rtc::Colour{1, 0.9, 0.9};
  floorMaterial.specular = 0;
  floor.setTransformationMatrix(rtc::scalingMatrix(10, 0.01f, 10));
  world.objects.push_back(std::make_unique<rtc::Sphere>(floor));

  auto leftWall = rtc::sphere();
  leftWall.setTransformationMatrix(
      rtc::translationMatrix(0, 0, 5) *
      rtc::rotationMatrixY(-std::numbers::pi_v<float> / 4) *
      rtc::rotationMatrixX(std::numbers::pi_v<float> / 2) *
      rtc::scalingMatrix(10, 0.01f, 10));
  leftWall.setMaterial(floor.getMaterial());
  world.objects.push_back(std::make_unique<rtc::Sphere>(leftWall));

  auto rightWall = rtc::sphere();
  rightWall.setTransformationMatrix(
      rtc::translationMatrix(0, 0, 5) *
      rtc::rotationMatrixY(std::numbers::pi_v<float> / 4) *
      rtc::rotationMatrixX(std::numbers::pi_v<float> / 2) *
      rtc::scalingMatrix(10, 0.01f, 10));
  rightWall.setMaterial(floor.getMaterial());
  world.objects.push_back(std::make_unique<rtc::Sphere>(rightWall));

  auto middle = rtc::sphere();
  middle.setTransformationMatrix(rtc::translationMatrix(-0.5f, 1, 0.5f));
  auto middleMaterial = middle.getMaterial();
  middleMaterial.colour = rtc::Colour{0.1f, 1, 0.5f};
  middleMaterial.diffuse = 0.7f;
  middleMaterial.specular = 0.3f;
  middle.setMaterial(middleMaterial);
  world.objects.push_back(std::make_unique<rtc::Sphere>(middle));

  auto right = rtc::sphere();
  right.setTransformationMatrix(rtc::translationMatrix(1.5f, 0.5f, -0.5f) *
                                rtc::scalingMatrix(0.5f, 0.5f, 0.5f));
  auto rightMaterial = right.getMaterial();
  rightMaterial.colour = rtc::Colour{0.5f, 1, 0.1f};
  rightMaterial.diffuse = 0.7f;
  rightMaterial.specular = 0.3f;
  right.setMaterial(rightMaterial);
  world.objects.push_back(std::make_unique<rtc::Sphere>(right));

  auto left = rtc::sphere();
  left.setTransformationMatrix(rtc::translationMatrix(-1.5f, 0.33f, -0.75f) *
                               rtc::scalingMatrix(0.33f, 0.33f, 0.33f));
  auto leftMaterial = left.getMaterial();
  leftMaterial.colour = rtc::Colour{1, 0.8f, 0.1f};
  leftMaterial.diffuse = 0.7f;
  leftMaterial.specular = 0.3f;
  left.setMaterial(leftMaterial);
  world.objects.push_back(std::make_unique<rtc::Sphere>(left));

  world.light = rtc::Light{rtc::Colour{1, 1, 1}, rtc::point(-10, 10, -10)};

  rtc::Camera camera{200, 200, std::numbers::pi_v<float> / 3};
  camera.setTransform(rtc::viewTransform(
      rtc::point(0, 1.5f, -5), rtc::point(0, 1, 0), rtc::vector(0, 1, 0)));

  const rtc::Canvas canvas = camera.render(world);
  std::ofstream file;
  file.open("Chapter7.ppm");
  file << canvas.toPPM();
  file.close();
  return 0;
}

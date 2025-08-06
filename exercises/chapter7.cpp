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
  floor.material.colour = rtc::Colour{1, 0.9, 0.9};
  floor.material.specular = 0;
  floor.transform = rtc::scalingMatrix(10, 0.01f, 10);
  world.objects.push_back(std::make_unique<rtc::Sphere>(floor));

  auto leftWall = rtc::sphere();
  leftWall.transform = rtc::translationMatrix(0, 0, 5) *
                       rtc::rotationMatrixY(-std::numbers::pi_v<float> / 4) *
                       rtc::rotationMatrixX(std::numbers::pi_v<float> / 2) *
                       rtc::scalingMatrix(10, 0.01f, 10);
  leftWall.material = floor.material;
  world.objects.push_back(std::make_unique<rtc::Sphere>(leftWall));

  auto rightWall = rtc::sphere();
  rightWall.transform = rtc::translationMatrix(0, 0, 5) *
                        rtc::rotationMatrixY(std::numbers::pi_v<float> / 4) *
                        rtc::rotationMatrixX(std::numbers::pi_v<float> / 2) *
                        rtc::scalingMatrix(10, 0.01f, 10);
  rightWall.material = floor.material;
  world.objects.push_back(std::make_unique<rtc::Sphere>(rightWall));

  auto middle = rtc::sphere();
  middle.transform = rtc::translationMatrix(-0.5f, 1, 0.5f);
  middle.material.colour = rtc::Colour{0.1f, 1, 0.5f};
  middle.material.diffuse = 0.7f;
  middle.material.specular = 0.3f;
  world.objects.push_back(std::make_unique<rtc::Sphere>(middle));

  auto right = rtc::sphere();
  right.transform = rtc::translationMatrix(1.5f, 0.5f, -0.5f) *
                    rtc::scalingMatrix(0.5f, 0.5f, 0.5f);
  right.material.colour = rtc::Colour{0.5f, 1, 0.1f};
  right.material.diffuse = 0.7f;
  right.material.specular = 0.3f;
  world.objects.push_back(std::make_unique<rtc::Sphere>(right));

  auto left = rtc::sphere();
  left.transform = rtc::translationMatrix(-1.5f, 0.33f, -0.75f) *
                   rtc::scalingMatrix(0.33f, 0.33f, 0.33f);
  middle.material.colour = rtc::Colour{1, 0.8f, 0.1f};
  middle.material.diffuse = 0.7f;
  middle.material.specular = 0.3f;
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

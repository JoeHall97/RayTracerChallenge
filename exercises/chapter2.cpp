#include <RayTracerChallenge/objects/canvas.hpp>
#include <RayTracerChallenge/datastructures/vec4.hpp>
#include <fstream>
#include <iostream>

class Projectile {
public:
  rtc::Vec4 pointPosition;
  rtc::Vec4 vecVelocity;

  Projectile(const rtc::Vec4 &pos, const rtc::Vec4 &vel) : pointPosition{pos},
    vecVelocity{vel} {
  }
};

class Environment {
public:
  rtc::Vec4 vecGravity;
  rtc::Vec4 vecWind;

  Environment(const rtc::Vec4 &grav, const rtc::Vec4 &wind) : vecGravity{grav},
    vecWind{wind} {
  }
};

void tick(const Environment &env, Projectile &proj) {
  const auto point = proj.pointPosition + proj.vecVelocity;
  const auto vel = proj.vecVelocity + env.vecGravity + env.vecWind;
  proj.pointPosition = point;
  proj.vecVelocity = vel;
}

int main() {
  std::cout << "Hello" << '\n';
  Projectile proj{rtc::point(0, 1, 0),
                  rtc::vector(1, 1.8, 0).normalise() * 10.8};
  const Environment env{rtc::vector(0, -0.1, 0), rtc::vector(-0.01, 0, 0)};
  rtc::Canvas c{900, 500};
  const rtc::Colour red{1, 0, 0};

  while (proj.pointPosition.y > 0.000001) {
    c.writePixel(static_cast<std::size_t>(proj.pointPosition.x),
                 c.getHeight() - static_cast<std::size_t>(proj.pointPosition.y),
                 red);
    tick(env, proj);
  }

  std::ofstream file;
  file.open("Chapter2.ppm");
  file << c.toPPM();
  file.close();

  return 0;
}
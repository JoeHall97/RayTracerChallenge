#include <RayTracerChallenge/datastructures/vec4.hpp>
#include <RayTracerChallenge/objects/canvas.hpp>
#include <fstream>

using rtc::Vec4;

struct Projectile {
  Vec4 pointPosition;
  Vec4 vecVelocity;

  Projectile(const Vec4 &pos, const Vec4 &vel)
    : pointPosition{pos}, vecVelocity{vel} {
  }
};

struct Environment {
  Vec4 vecGravity;
  Vec4 vecWind;

  Environment(const Vec4 &grav, const Vec4 &wind)
    : vecGravity{grav}, vecWind{wind} {
  }
};

void tick(const Environment &env, Projectile &proj) {
  const auto point = proj.pointPosition + proj.vecVelocity;
  const auto vel = proj.vecVelocity + env.vecGravity + env.vecWind;
  proj.pointPosition = point;
  proj.vecVelocity = vel;
}

int main() {
  Projectile proj{rtc::point(0, 1, 0),
                  rtc::vector(1, 1.8, 0).normalise() * 10.8};
  const Environment env{rtc::vector(0, -0.1, 0), rtc::vector(-0.01, 0, 0)};
  rtc::Canvas c{900, 500};
  const rtc::Colour red{1, 0, 0};

  while (proj.pointPosition.y > 0.000001f) {
    c.writePixel(static_cast<std::size_t>(proj.pointPosition.x),
                 c.getHeight() - static_cast<std::size_t>(proj.pointPosition.y),
                 red);
    tick(env, proj);
  }

  std::ofstream file;
  file.open("Chapter3.ppm");
  file << c.toPPM();
  file.close();

  return 0;
}
#include "iostream"
#include "tuple.h"
#include <thread>

class Projectile
{
  public:
    Tuple pointPosition;
    Tuple vecVelocity;
    Projectile(Tuple pos, Tuple vel) : pointPosition{pos}, vecVelocity{vel}
    {
    }
};

class Environment
{
  public:
    Tuple vecGravity;
    Tuple vecWind;
    Environment(Tuple grav, Tuple wind) : vecGravity{grav}, vecWind{wind}
    {
    }
};

void tick(const Environment &env, Projectile &proj)
{
    auto point = proj.pointPosition + proj.vecVelocity;
    auto vel = proj.vecVelocity + env.vecGravity + env.vecWind;
    proj.pointPosition = point;
    proj.vecVelocity = vel;
}

int main()
{
    std::cout << "Hello" << '\n';
    Projectile proj{point(0, 1, 0), vector(1, 1, 0).normarilise()};
    Environment env{vector(0, -0.1, 0), vector(-0.01, 0, 0)};

    while (proj.pointPosition.y > 0.000001)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << proj.pointPosition << '\n';
        tick(env, proj);
    }
    std::cout << proj.pointPosition << '\n';
}

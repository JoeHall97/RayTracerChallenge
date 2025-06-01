#include "canvas.h"
#include "coord_tuple.h"
#include <fstream>
#include <iostream>
#include <thread>

class Projectile
{
  public:
    CoordTuple pointPosition;
    CoordTuple vecVelocity;
    Projectile(CoordTuple pos, CoordTuple vel) : pointPosition{pos}, vecVelocity{vel}
    {
    }
};

class Environment
{
  public:
    CoordTuple vecGravity;
    CoordTuple vecWind;
    Environment(CoordTuple grav, CoordTuple wind) : vecGravity{grav}, vecWind{wind}
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
    Projectile proj{point(0, 1, 0), vector(1, 1.8, 0).normarilise() * 10.8};
    Environment env{vector(0, -0.1, 0), vector(-0.01, 0, 0)};
    Canvas c{900, 500};
    ColourTuple red{1, 0, 0};

    while (proj.pointPosition.y > 0.000001)
    {
        c.writePixel(proj.pointPosition.x, c.height - proj.pointPosition.y, red);
        tick(env, proj);
    }

    std::ofstream file;
    file.open("test.ppm");
    file << c.toPPM();
    file.close();

    return 0;
}

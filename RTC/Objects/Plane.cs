using RTC.Datastructures;
using RTC.Helpers;
using RTC.Primitives;

namespace RTC.Objects;

public class Plane : Shape
{
    protected override Intersection[] LocalIntersect(Ray localRay)
    {
        if (Math.Abs(localRay.Direction.Y) < Helper.Epsilon) return [];

        var t = -localRay.Origin.Y / localRay.Direction.Y;
        return [new Intersection(this, t)];
    }

    protected override Vec4 LocalNormalAt(Vec4 objectPoint)
    {
        return Vec4.Vector(0, 1, 0);
    }
}
using RTC.Datastructures;
using RTC.Objects;
using Shouldly;

namespace RTC.UnitTests.Objects;

public class SphereUnitTests
{
    public static IEnumerable<object[]> SphereIntersectTestData =>
    [
        // a ray intersects a sphere at two points
        [
            new Ray(Vec4.Point(0, 0, -5), Vec4.Vector(0, 0, 1)),
            new [] { 4.0d, 6.0d },
            Matrix.IdentityMatrix(4)
        ],
        // a ray intersects a sphere at a tangent
        [
            new Ray(Vec4.Point(0, 1, -5), Vec4.Vector(0, 0, 1)),
            new [] { 5.0d, 5.0d },
            Matrix.IdentityMatrix(4)
        ],
        // a ray misses a sphere
        [
            new Ray(Vec4.Point(0, 2, -5), Vec4.Vector(0, 0, 1)),
            Array.Empty<double>(),
            Matrix.IdentityMatrix(4)
        ],
        // a ray originates inside a sphere
        [
            new Ray(Vec4.Point(0, 0, 0), Vec4.Vector(0, 0, 1)),
            new [] { -1.0d, 1.0d },
            Matrix.IdentityMatrix(4)
        ],
        // a sphere is behind the ray
        [
            new Ray(Vec4.Point(0, 0, 5), Vec4.Vector(0, 0, 1)),
            new [] { -6.0d, -4.0d },
            Matrix.IdentityMatrix(4)
        ],
        // a scaled sphere 
        [
            new Ray(Vec4.Point(0, 0, -5), Vec4.Vector(0, 0, 1)),
            new [] { 3.0d, 7.0d },
            Matrix.ScalingMatrix(2, 2, 2)
        ],
        // a translated sphere
        [
            new Ray(Vec4.Point(0, 0, -5), Vec4.Vector(0, 0, 1)),
            Array.Empty<double>(),
            Matrix.TranslationMatrix(5, 0, 0)
        ],
    ];

    [Theory]
    [MemberData(nameof(SphereIntersectTestData))]
    public void TestSphereIntersections(Ray r, double[] intersections, Matrix transformation)
    {
        var s = new Sphere(transformation);
        var xs = s.Intersect(r);
        
        xs.Length.ShouldBe(intersections.Length);
        for (var i = 0; i < xs.Length; i++)
        {
            xs[i].T.ShouldBe(intersections[i]);
            xs[i].Shape.ShouldBe(s);
        }
    }
}
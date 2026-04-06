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
            new [] { 5.0d },
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

    public static IEnumerable<object[]> SphereNormalTestData =>
    [
        // The normal on a sphere at a point on the x-axis
        [Vec4.Point(1, 0, 0), Vec4.Vector(1, 0, 0), Matrix.IdentityMatrix(4)],
        // The normal on a sphere at a point on the y-axis
        [Vec4.Point(0, 1, 0), Vec4.Vector(0, 1, 0), Matrix.IdentityMatrix(4)],
        // The normal on a sphere at a point on the z-axis
        [Vec4.Point(0, 0, 1), Vec4.Vector(0, 0, 1), Matrix.IdentityMatrix(4)],
        // The normal on a sphere at a non-axial point
        [Vec4.Point(Math.Sqrt(3) / 3, Math.Sqrt(3) / 3, Math.Sqrt(3) / 3), Vec4.Vector(Math.Sqrt(3) / 3, Math.Sqrt(3) / 3, Math.Sqrt(3) / 3), Matrix.IdentityMatrix(4)],
        // Computing the normal on a translated sphere
        [Vec4.Point(0, 1.70711d, -0.70711d), Vec4.Vector(0, 0.70711d, -0.70711d), Matrix.TranslationMatrix(0, 1, 0)],
        // Computing the normal on a transformed sphere
        [Vec4.Point(0, Math.Sqrt(2) / 2, -Math.Sqrt(2) / 2), Vec4.Vector(0, 0.97014d, -0.24254d), Matrix.ScalingMatrix(1, 0.5d, 1) * Matrix.RotationZMatrix(Math.PI / 5)]
    ];
    
    [Theory]
    [MemberData(nameof(SphereIntersectTestData))]
    public void TestSphereIntersections(Ray r, double[] intersections, Matrix transformation)
    {
        var s = new Sphere(transformation);
        var xs = s.Intersect(r);
        
        xs.Values.Count.ShouldBe(intersections.Length);
        for (var i = 0; i < xs.Values.Count; i++)
        {
            xs.Values.ElementAt(i).T.ShouldBe(intersections[i]);
            xs.Values.ElementAt(i).Shape.ShouldBe(s);
        }
    }
    
    [Theory]
    [MemberData(nameof(SphereNormalTestData))]
    public void TestSphereNormal(Vec4 p, Vec4 expected, Matrix transformation)
    {
        var s = new Sphere(transformation);
        s.NormalAt(p).ShouldBe(expected);
    }
    
    [Fact]
    public void TestNormalIsANormalizedVector()
    {
        var s = new Sphere();
        var n = s.NormalAt(Vec4.Point(Math.Sqrt(3) / 3, Math.Sqrt(3) / 3, Math.Sqrt(3) / 3));
        n.ShouldBe(n.Normalised);
    }
}
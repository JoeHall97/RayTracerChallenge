using RTC.Datastructures;
using RTC.Objects;
using RTC.Primitives;
using Shouldly;

namespace RTC.UnitTests.Objects;

public class PlaneUnitTests
{
    public static IEnumerable<object[]> IntersectionTestData =>
    [
        // a ray parallel to the plane
        [new Ray(Vec4.Point(0, 10, 0), Vec4.Vector(0, 0, 1)), Array.Empty<Intersection>()],
        // a coplanar intersection with a ray
        [new Ray(Vec4.Point(0, 0, 0), Vec4.Vector(0, 0, 1)), Array.Empty<Intersection>()],
        // a ray intersecting a plane from above
        [new Ray(Vec4.Point(0, 1, 0), Vec4.Vector(0, -1, 0)), new[] { new Intersection(new Plane(), 1) }],
        // a ray intersecting a plane from below
        [new Ray(Vec4.Point(0, -1, 0), Vec4.Vector(0, 1, 0)), new[] { new Intersection(new Plane(), 1) }]
    ];

    [Fact]
    public void TestPlaneNormalAt()
    {
        var p = new Plane();

        p.NormalAt(Vec4.Point(0, 0, 0)).ShouldBe(Vec4.Vector(0, 1, 0));
        p.NormalAt(Vec4.Point(10, 0, -10)).ShouldBe(Vec4.Vector(0, 1, 0));
        p.NormalAt(Vec4.Point(-5, 0, 150)).ShouldBe(Vec4.Vector(0, 1, 0));
    }

    [Theory]
    [MemberData(nameof(IntersectionTestData))]
    public void TestPlaneIntersections(Ray ray, Intersection[] expected)
    {
        var p = new Plane();
        var xs = p.Intersect(ray);

        xs.Length.ShouldBe(expected.Length);

        for (var i = 0; i < xs.Length; i++)
        {
            xs[i].T.ShouldBe(expected[i].T);
            xs[i].Shape.ShouldBe(p);
        }
    }
}
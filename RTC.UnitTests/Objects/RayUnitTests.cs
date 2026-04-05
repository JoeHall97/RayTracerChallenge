using RTC.Datastructures;
using RTC.Objects;
using Shouldly;

namespace RTC.UnitTests.Objects;

public class RayUnitTests
{
    public static IEnumerable<object[]> RayTransformationTestData =>
    [
        [new Ray(Vec4.Point(1, 2, 3), Vec4.Vector(0, 1, 0)), Matrix.TranslationMatrix(3, 4, 5), Vec4.Point(4, 6, 8), Vec4.Vector(0, 1, 0)],
        [new Ray(Vec4.Point(1, 2, 3), Vec4.Vector(0, 1, 0)), Matrix.ScalingMatrix(2, 3, 4), Vec4.Point(2, 6, 12), Vec4.Vector(0, 3, 0)],
    ];
    
    [Fact]
    public void TestComputingAPointFromDistance()
    {
        var r = new Ray(Vec4.Point(2, 3, 4), Vec4.Vector(1, 0, 0));
        r.Position(0).ShouldBe(Vec4.Point(2, 3, 4));
        r.Position(1).ShouldBe(Vec4.Point(3, 3, 4));
        r.Position(-1).ShouldBe(Vec4.Point(1, 3, 4));
        r.Position(2.5).ShouldBe(Vec4.Point(4.5, 3, 4));
    }

    [Theory]
    [MemberData(nameof(RayTransformationTestData))]
    public void TestRayTransformation(Ray r, Matrix m, Vec4 expectedOrigin, Vec4 expectedDirection)
    {
        var transformedRay = r.Transform(m);
        transformedRay.Origin.ShouldBe(expectedOrigin);
        transformedRay.Direction.ShouldBe(expectedDirection);
    }
}
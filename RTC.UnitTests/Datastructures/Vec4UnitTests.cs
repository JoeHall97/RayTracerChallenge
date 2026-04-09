using RTC.Datastructures;
using RTC.Helpers;
using Shouldly;

namespace RTC.UnitTests.Datastructures;

public class Vec4UnitTests
{
    public static IEnumerable<object[]> ReflectionTestData =>
    [
        // Reflecting a vector approaching at 45 degrees
        [Vec4.Vector(1, -1, 0), Vec4.Vector(0, 1, 0), Vec4.Vector(1, 1, 0)],
        // Reflecting a vector off a slanted surface
        [Vec4.Vector(0, -1, 0), Vec4.Vector(Math.Sqrt(2) / 2, Math.Sqrt(2) / 2, 0), Vec4.Vector(1, 0, 0)]
    ];
    
    public static IEnumerable<object[]> MagnitudeTestData =>
    [
        [Vec4.Vector(1, 0, 0), 1d],
        [Vec4.Vector(1, 2, 3), Math.Sqrt(14)],
        [Vec4.Vector(-1, -2, -3), Math.Sqrt(14)]
    ];

    public static IEnumerable<object[]> NormalizeTestData =>
    [
        [Vec4.Vector(4, 0, 0), Vec4.Vector(1, 0, 0)],
        [
            Vec4.Vector(1, 2, 3), Vec4.Vector(0.26726, 0.53452, 0.80178)
        ] // expected ~= vec(1/sqrt(14), 2/sqrt(14), 3/sqrt(14))
    ];

    [Theory]
    [MemberData(nameof(MagnitudeTestData))]
    public void TestMagnitude(Vec4 vec, double expected)
    {
        vec.Magnitude.IsEqual(expected).ShouldBeTrue();
    }

    [Theory]
    [MemberData(nameof(NormalizeTestData))]
    public void TestNormalize(Vec4 vec, Vec4 expected)
    {
        vec.Normalise().ShouldBe(expected);
    }

    [Fact]
    public void TestMagnitudeOfNormalisedVector()
    {
        var vec = Vec4.Vector(1, 2, 3);
        vec.Normalise().Magnitude.IsEqual(1).ShouldBeTrue();
    }

    [Fact]
    public void TestDotProductOfTwoVectors()
    {
        var a = Vec4.Vector(1, 2, 3);
        var b = Vec4.Vector(2, 3, 4);
        a.Dot(b).IsEqual(20).ShouldBeTrue();
    }

    [Fact]
    public void TestCrossProductOfTwoVectors()
    {
        var a = Vec4.Vector(1, 2, 3);
        var b = Vec4.Vector(2, 3, 4);
        a.Cross(b).ShouldBe(Vec4.Vector(-1, 2, -1));
        b.Cross(a).ShouldBe(Vec4.Vector(1, -2, 1));
    }
    
    [Theory]
    [MemberData(nameof(ReflectionTestData))]
    public void TestReflectionOfVector(Vec4 v, Vec4 n, Vec4 expected)
    {
        v.Reflect(n).ShouldBe(expected);
    }
}
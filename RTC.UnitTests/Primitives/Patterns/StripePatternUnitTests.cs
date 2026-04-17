using RTC.Datastructures;
using RTC.Objects;
using RTC.Primitives;
using RTC.Primitives.Patterns;
using Shouldly;

namespace RTC.UnitTests.Primitives.Patterns;

public class StripePatternUnitTests
{
    public static IEnumerable<object[]> StripePatternTestData =>
    [
        // stripe pattern is constant in y
        [Vec4.Point(0, 0, 0), Colour.White],
        [Vec4.Point(0, 1, 0), Colour.White],
        [Vec4.Point(0, 2, 0), Colour.White],
        // stripe pattern is constant in z
        [Vec4.Point(0, 0, 0), Colour.White],
        [Vec4.Point(0, 0, 1), Colour.White],
        [Vec4.Point(0, 0, 2), Colour.White],
        // stripe pattern is alternates in x
        [Vec4.Point(0, 0, 0), Colour.White],
        [Vec4.Point(0.9, 0, 0), Colour.White],
        [Vec4.Point(1, 0, 0), Colour.Black],
        [Vec4.Point(-0.1, 0, 0), Colour.Black],
        [Vec4.Point(-1, 0, 0), Colour.Black],
        [Vec4.Point(-1.1, 0, 0), Colour.White]
    ];

    public static IEnumerable<object[]> StripePatternObjectTestData =>
    [
        // stripes with an object transformation
        [
            new Sphere(Matrix.ScalingMatrix(2, 2, 2)),
            new StripePattern(Colour.White, Colour.Black),
            Vec4.Point(1.5d, 0, 0),
            Colour.White
        ],
        // stripes with a pattern transformation
        [
            new Sphere(),
            new StripePattern(Colour.White, Colour.Black, Matrix.ScalingMatrix(2, 2, 2)),
            Vec4.Point(1.5d, 0, 0),
            Colour.White
        ],
        // stripes with both an object and a pattern transformation
        [
            new Sphere(Matrix.ScalingMatrix(2, 2, 2)),
            new StripePattern(Colour.White, Colour.Black, Matrix.TranslationMatrix(0.5d, 0, 0)),
            Vec4.Point(2.5d, 0, 0),
            Colour.White
        ]
    ];

    [Theory]
    [MemberData(nameof(StripePatternTestData))]
    public void TestStripePattern(Vec4 point, Colour expectedColour)
    {
        var pattern = new StripePattern(Colour.White, Colour.Black);
        pattern.PatternAt(point).ShouldBe(expectedColour);
    }

    [Theory]
    [MemberData(nameof(StripePatternObjectTestData))]
    public void TestStripePatternOnAnObject(Sphere sphere, StripePattern pattern, Vec4 point, Colour expectedColour)
    {
        pattern.PatternAtObject(sphere, point).ShouldBe(expectedColour);
    }
}
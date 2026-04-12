using RTC.Datastructures;
using RTC.Objects;
using RTC.Primitives;
using RTC.Primitives.Patterns;
using Shouldly;

namespace RTC.UnitTests.Primitives.Patterns;

public class CheckerPatternUnitTests
{
    public static IEnumerable<object[]> CheckerPatternTestData =>
    [
        // checker pattern should repeat in x
        [Vec4.Point(0, 0, 0), Colour.White],
        [Vec4.Point(0.99d, 0, 0), Colour.White],
        [Vec4.Point(1.01d, 0, 0), Colour.Black],
        // checker pattern should repeat in y
        [Vec4.Point(0, 0, 0), Colour.White],
        [Vec4.Point(0, 0.99d, 0), Colour.White],
        [Vec4.Point(0, 1.01d, 0), Colour.Black],
        // checker pattern should repeat in z
        [Vec4.Point(0, 0, 0), Colour.White],
        [Vec4.Point(0, 0, 0.99d), Colour.White],
        [Vec4.Point(0, 0, 1.01d), Colour.Black]
    ];

    [Theory]
    [MemberData(nameof(CheckerPatternTestData))]
    public void TestCheckerPattern(Vec4 point, Colour expectedColour)
    {
        var pattern = new CheckerPattern(Colour.White, Colour.Black);
        var s = new Sphere();
        pattern.PatternAt(s, point).ShouldBe(expectedColour);
    }
}
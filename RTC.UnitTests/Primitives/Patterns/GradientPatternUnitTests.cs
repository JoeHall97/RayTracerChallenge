using RTC.Datastructures;
using RTC.Primitives;
using RTC.Primitives.Patterns;
using Shouldly;

namespace RTC.UnitTests.Primitives.Patterns;

public class GradientPatternUnitTests
{
    [Fact]
    public void TestGradientPattern()
    {
        var pattern = new GradientPattern(Colour.White, Colour.Black);

        pattern.PatternAt(Vec4.Point(0, 0, 0)).ShouldBe(Colour.White);
        pattern.PatternAt(Vec4.Point(0.25d, 0, 0)).ShouldBe(new Colour(0.75d, 0.75d, 0.75d));
        pattern.PatternAt(Vec4.Point(0.5d, 0, 0)).ShouldBe(new Colour(0.5d, 0.5d, 0.5d));
        pattern.PatternAt(Vec4.Point(0.75d, 0, 0)).ShouldBe(new Colour(0.25d, 0.25d, 0.25d));
    }
}